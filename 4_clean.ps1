# ================================================
# Script PowerShell de nettoyage pour projet JUCE
# Supprime build/, packages, sauvegardes
# Compatible Windows PowerShell
# ================================================

$ScriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
$JUCE_PROJ = Split-Path $ScriptDir -Parent
$PROJECT = Split-Path $ScriptDir -Leaf
$BUILD_DIR = Join-Path $ScriptDir "build"

Write-Host "🧹 Nettoyage du projet : $PROJECT"

# Suppression du dossier build
if (Test-Path $BUILD_DIR) {
    Remove-Item -Recurse -Force $BUILD_DIR
    Write-Host "✅ Dossier $BUILD_DIR supprimé."
} else {
    Write-Host "ℹ️ Aucun dossier $BUILD_DIR à supprimer."
}

# Suppression des fichiers de packaging et temporaires
$extraFiles = @(
    "install_manifest.txt",
    "*.tar.gz", "*.pkg", "*.deb", "*.exe", "*.zip",
    "CMakeLists.txt.bak", "*.old", "*.tmp"
)

foreach ($pattern in $extraFiles) {
    Get-ChildItem -Path $ScriptDir -Filter $pattern -File -ErrorAction SilentlyContinue | Remove-Item -Force -ErrorAction SilentlyContinue
}

Write-Host "✅ Nettoyage terminé."
Write-Host "💡 Vous pouvez relancer .\\2_build.ps1 pour recompiler."
