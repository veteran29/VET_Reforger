param (
    [string] $workspace
)

$documentsPath = [Environment]::GetFolderPath("MyDocuments");
$addonsPath = "$documentsPath/My Games/ArmaReforger/addons";

if ((Test-Path -Path $addonsPath) -eq $False) {
    Throw 'ArmaReforger addons folder not found.';
}

$sourceDirs = Get-ChildItem -Path $workspace -Recurse -Filter addon.gproj | Select-Object -ExpandProperty DirectoryName -Unique

foreach ($sourceDir in $sourceDirs) {
    $linkPath = "$addonsPath/$(Split-Path -Path $sourceDir -Leaf)";

    New-Item -ItemType Junction -Path $linkPath -Target $sourceDir
}

Write-Information "Linked project mods into ArmaReforger/addons directory.";
