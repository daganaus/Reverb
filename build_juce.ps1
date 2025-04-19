# ================================================
# Script PowerShell pour construire un projet JUCE sous Windows
# Compatible avec Visual Studio + terminal intégré de VSC
# Options : --release / --fast
# ================================================

$JUCE_PROJ = "$HOME\c++\musique\JUCE_fred"
$PROJECT = "Template"
$JUCE_DIR = "$JUCE_PROJ\JUCE-master"
$BUILD_DIR = "build"

$BUILD_TYPE = "Debug"
$FULL_REBUILD = $true

# Traitement des arguments
foreach ($arg in $args) {
    switch ($arg) {
        "--release" { $BUILD_TYPE = "Release" }
        "--fast"    { $FULL_REBUILD = $false }
    }
}

Write-Host "🚀 Compilation de $PROJECT [$BUILD_TYPE]" -ForegroundColor Green

# Vérifie que JUCE_DIR contient bien un CMakeLists.txt
if (!(Test-Path "$JUCE_DIR\CMakeLists.txt")) {
    Write-Host "❌ JUCE_DIR invalide : $JUCE_DIR" -ForegroundColor Red
    exit 1
}

# Aller dans le dossier projet
$projPath = "$JUCE_PROJ\$PROJECT"
if (!(Test-Path $projPath)) {
    Write-Host "❌ Projet introuvable : $projPath" -ForegroundColor Red
    exit 1
}

Set-Location $projPath

# Nettoyage si FULL_REBUILD
if ($FULL_REBUILD -and (Test-Path $BUILD_DIR)) {
    Write-Host "🧹 Suppression du dossier build..." -ForegroundColor Yellow
    Remove-Item -Recurse -Force $BUILD_DIR
}

if (!(Test-Path $BUILD_DIR)) {
    New-Item -ItemType Directory -Path $BUILD_DIR | Out-Null
}

Set-Location $BUILD_DIR

# Configuration CMake (si nécessaire)
if ($FULL_REBUILD -or !(Test-Path "CMakeCache.txt")) {
    Write-Host "⚙️ Configuration CMake..." -ForegroundColor Cyan
    cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DJUCE_DIR="$JUCE_DIR" ..
    if ($LASTEXITCODE -ne 0) {
        Write-Host "❌ Erreur de configuration CMake" -ForegroundColor Red
        exit 1
    }
}

# Compilation
Write-Host "🛠️ Compilation en cours..." -ForegroundColor Cyan
cmake --build . --config $BUILD_TYPE -- -m

if ($LASTEXITCODE -ne 0) {
    Write-Host "❌ Erreur à la compilation" -ForegroundColor Red
    exit 1
}

Write-Host "✅ Compilation réussie !" -ForegroundColor Green

# Packaging avec cpack si FULL_REBUILD
if ($FULL_REBUILD) {
    Write-Host "📦 Packaging..." -ForegroundColor Cyan
    cpack .
    if ($LASTEXITCODE -ne 0) {
        Write-Host "⚠️ Aucun package généré (ou cpack non configuré)" -ForegroundColor Yellow
    }
}

Set-Location $projPath
