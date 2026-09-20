[CmdletBinding()]
param(
    [string]$Version
)

$ErrorActionPreference = 'Stop'
$projectRoot = Split-Path -Parent $PSScriptRoot
$pluginRoot = Join-Path $projectRoot 'plugins/mellos-coding'
$pluginManifestPath = Join-Path $pluginRoot '.claude-plugin/plugin.json'
$marketplaceManifestPath = Join-Path $projectRoot '.claude-plugin/marketplace.json'
$codexManifestPath = Join-Path $pluginRoot '.codex-plugin/plugin.json'

foreach ($requiredPath in @($pluginManifestPath, $marketplaceManifestPath, $codexManifestPath)) {
    if (-not (Test-Path -LiteralPath $requiredPath -PathType Leaf)) {
        throw "Required manifest is missing: $requiredPath"
    }
}
Get-Command claude -ErrorAction Stop | Out-Null

function Read-ManifestText([string]$path) {
    Get-Content -LiteralPath $path -Raw -Encoding utf8
}

function Set-ManifestVersion([string]$path, [string]$currentVersion, [string]$nextVersion) {
    $text = Read-ManifestText $path
    $pattern = '"version"\s*:\s*"' + [regex]::Escape($currentVersion) + '"'
    $matchCount = ([regex]::Matches($text, $pattern)).Count
    if ($matchCount -ne 1) {
        throw "Expected exactly one version $currentVersion in $path, found $matchCount"
    }
    $replaced = [regex]::Replace($text, $pattern, '"version": "' + $nextVersion + '"')
    [IO.File]::WriteAllText($path, $replaced, [Text.UTF8Encoding]::new($false))
}

# Validate: the two Claude manifests must already agree, or the release identity is ambiguous.
$pluginManifest = Read-ManifestText $pluginManifestPath | ConvertFrom-Json
$marketplaceManifest = Read-ManifestText $marketplaceManifestPath | ConvertFrom-Json
$codexManifest = Read-ManifestText $codexManifestPath | ConvertFrom-Json

$pluginName = $pluginManifest.name
if ($pluginName -ne 'mellos-coding') { throw "Unexpected plugin identity: $pluginName" }
$marketplaceName = $marketplaceManifest.name
$entries = @($marketplaceManifest.plugins | Where-Object { $_.name -eq $pluginName })
if ($entries.Count -ne 1) { throw "Expected exactly one $pluginName entry in $marketplaceManifestPath" }
$entry = $entries[0]
$currentVersion = $pluginManifest.version
if ($entry.version -ne $currentVersion) {
    throw "Marketplace entry version $($entry.version) differs from plugin version $currentVersion"
}
$entrySource = (Join-Path $projectRoot $entry.source | Resolve-Path).Path
if ($entrySource -ne (Resolve-Path $pluginRoot).Path) {
    throw "Marketplace entry source $($entry.source) does not point at $pluginRoot"
}
if ($codexManifest.name -ne $pluginName) { throw "Codex manifest names a different plugin: $($codexManifest.name)" }

# Validate: the registered marketplace must be this project, so the sync cannot install someone else's source.
$registered = @(claude plugin marketplace list --json | ConvertFrom-Json | Where-Object { $_.name -eq $marketplaceName })
if ($LASTEXITCODE -ne 0) { throw 'Could not read the registered marketplaces.' }
if ($registered.Count -ne 1) {
    throw "Marketplace $marketplaceName is not registered; run: claude plugin marketplace add `"$projectRoot`""
}
if ($registered[0].source -ne 'directory') {
    throw "Marketplace $marketplaceName is registered from $($registered[0].source), not this working copy; inspect before syncing"
}
if ((Resolve-Path $registered[0].path).Path -ne (Resolve-Path $projectRoot).Path) {
    throw "Marketplace $marketplaceName points at $($registered[0].path), not $projectRoot"
}

# Prepare: one version identifies one plugin content, so both hosts' manifests move together.
# The Codex cachebuster keeps everything before '+', so its base version stays in step.
if ($Version) {
    if ($Version -notmatch '^\d+\.\d+\.\d+$') { throw "Version must be major.minor.patch: $Version" }
    if ($Version -eq $currentVersion) { throw "Version $Version is already the current version" }
    $nextVersion = $Version
} else {
    if ($currentVersion -notmatch '^(\d+)\.(\d+)\.(\d+)$') {
        throw "Cannot bump $currentVersion automatically; pass -Version"
    }
    $nextVersion = "$($Matches[1]).$($Matches[2]).$([int]$Matches[3] + 1)"
}

Set-ManifestVersion $pluginManifestPath $currentVersion $nextVersion
Set-ManifestVersion $marketplaceManifestPath $currentVersion $nextVersion
Set-ManifestVersion $codexManifestPath $codexManifest.version $nextVersion

claude plugin validate $projectRoot
if ($LASTEXITCODE -ne 0) { throw 'Marketplace manifest validation failed.' }
claude plugin validate $pluginRoot
if ($LASTEXITCODE -ne 0) { throw 'Plugin manifest validation failed.' }

# Commit: refresh the marketplace read, then reinstall at the new version.
claude plugin marketplace update $marketplaceName
if ($LASTEXITCODE -ne 0) { throw 'Marketplace refresh failed.' }
# -y answers the non-interactive install prompt; the source is this working copy, already verified above.
claude plugin update $pluginName -y
if ($LASTEXITCODE -ne 0) { throw 'Plugin update failed; the working copy is unchanged and can be retried.' }

$installed = @(claude plugin list --json | ConvertFrom-Json | Where-Object { $_.id -eq "$pluginName@$marketplaceName" })
if ($LASTEXITCODE -ne 0) { throw 'Could not verify the installed plugin.' }
if ($installed.Count -ne 1 -or -not $installed[0].enabled -or $installed[0].version -ne $nextVersion) {
    throw "Installed plugin does not match version $nextVersion or is disabled."
}
Write-Output "Installed and enabled $pluginName $nextVersion. Start a new Claude Code session to load it."
