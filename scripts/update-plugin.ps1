[CmdletBinding()]
param(
    [string]$CodexDirectory = $(if ($env:CODEX_HOME) { $env:CODEX_HOME } else { Join-Path $env:USERPROFILE '.codex' })
)

$ErrorActionPreference = 'Stop'
$projectRoot = Split-Path -Parent $PSScriptRoot
$pluginRoot = Join-Path $projectRoot 'plugins/mellos-coding'
$marketplacePath = Join-Path $env:USERPROFILE '.agents/plugins/marketplace.json'
$pluginTools = Join-Path $CodexDirectory 'skills/.system/plugin-creator/scripts'
$skillValidator = Join-Path $CodexDirectory 'skills/.system/skill-creator/scripts/quick_validate.py'

foreach ($requiredPath in @(
    $marketplacePath,
    $skillValidator,
    (Join-Path $pluginTools 'read_marketplace_name.py'),
    (Join-Path $pluginTools 'validate_plugin.py'),
    (Join-Path $pluginTools 'update_plugin_cachebuster.py')
)) {
    if (-not (Test-Path -LiteralPath $requiredPath -PathType Leaf)) {
        throw "Required local file is missing: $requiredPath"
    }
}
Get-Command python, codex -ErrorAction Stop | Out-Null

$marketplaceName = (& python -X utf8 (Join-Path $pluginTools 'read_marketplace_name.py') --marketplace-path $marketplacePath | Out-String).Trim()
if ($LASTEXITCODE -ne 0) { throw 'Marketplace name validation failed.' }

# Resolve the registered source, including the junction, before changing a version.
@'
import json
import sys
from pathlib import Path

marketplace = Path(sys.argv[1]).resolve(strict=True)
plugin = Path(sys.argv[2]).resolve(strict=True)
catalog = json.loads(marketplace.read_text(encoding="utf-8"))
entries = [entry for entry in catalog["plugins"] if entry["name"] == "mellos-coding"]
if len(entries) != 1:
    raise SystemExit("Expected exactly one mellos-coding marketplace entry")
source = entries[0]["source"]
if source.get("source") != "local":
    raise SystemExit("The registered plugin source must be local")
registered = (marketplace.parents[2] / source["path"]).resolve(strict=True)
if registered != plugin:
    raise SystemExit("Marketplace source differs from this project; inspect before installing")
manifest = json.loads((plugin / ".codex-plugin/plugin.json").read_text(encoding="utf-8"))
if manifest["name"] != "mellos-coding":
    raise SystemExit("Unexpected plugin identity")
print("Verified marketplace source matches this project")
'@ | & python -X utf8 - $marketplacePath $pluginRoot
if ($LASTEXITCODE -ne 0) { throw 'Plugin source verification failed.' }

foreach ($skill in Get-ChildItem -LiteralPath (Join-Path $pluginRoot 'skills') -Directory) {
    & python -X utf8 $skillValidator $skill.FullName
    if ($LASTEXITCODE -ne 0) { throw "Skill validation failed: $($skill.Name)" }
}
& python -X utf8 (Join-Path $pluginTools 'validate_plugin.py') $pluginRoot
if ($LASTEXITCODE -ne 0) { throw 'Plugin validation failed.' }

& python -X utf8 (Join-Path $pluginTools 'update_plugin_cachebuster.py') $pluginRoot
if ($LASTEXITCODE -ne 0) { throw 'Plugin version update failed.' }

& codex plugin add "mellos-coding@$marketplaceName" --json
if ($LASTEXITCODE -ne 0) { throw 'Plugin installation failed; source remains available for retry.' }

$installedJson = & codex plugin list --marketplace $marketplaceName --json
if ($LASTEXITCODE -ne 0) { throw 'Could not verify installed plugin status.' }
$installed = @(($installedJson | ConvertFrom-Json).installed | Where-Object { $_.name -eq 'mellos-coding' })
$manifest = Get-Content -LiteralPath (Join-Path $pluginRoot '.codex-plugin/plugin.json') -Raw -Encoding utf8 | ConvertFrom-Json
if ($installed.Count -ne 1 -or -not $installed[0].installed -or -not $installed[0].enabled -or $installed[0].version -ne $manifest.version) {
    throw 'Installed plugin status or version does not match the source.'
}
Write-Output "Installed and enabled mellos-coding $($manifest.version). Start a new task to test the updated skills."
