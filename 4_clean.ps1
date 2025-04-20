# ================================================
# Script PowerShell de nettoyage pour projet JUCE
# Supprime build/, packages, sauvegardes
# Compatible Windows PowerShell
# ================================================

$ScriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
$PROJECT = Split-Path $ScriptDir -Leaf
$BUILD_DIR = Join-Path $ScriptDir "build"

Write-Host "`nNettoyage du projet : $PROJECT"

# Suppression du dossier build
if (Test-Path $BUILD_DIR) {
    Remove-Item -Recurse -Force $BUILD_DIR
    Write-Host "Dossier $BUILD_DIR supprime."
} else {
    Write-Host "Aucun dossier $BUILD_DIR a supprimer."
}

# Suppression des fichiers de packaging et temporaires
$patterns = @(
    "install_manifest.txt",
    "*.tar.gz", "*.pkg", "*.deb", "*.exe", "*.zip",
    "CMakeLists.txt.bak", "*.old", "*.tmp"
)

foreach ($pattern in $patterns) {
    Get-ChildItem -Path $ScriptDir -Filter $pattern -File -ErrorAction SilentlyContinue | Remove-Item -Force -ErrorAction SilentlyContinue
}

Write-Host "Nettoyage termine."
Write-Host "Vous pouvez relancer .\\2_build.ps1 pour recompiler.`n"
