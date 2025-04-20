# ================================================
# Script PowerShell pour créer un projet JUCE
# Usage : .\1_setup.ps1 NomDuProjet
# Compatible PowerShell Windows
# ================================================

param(
    [Parameter(Mandatory = $true)]
    [string]$NewProjectName
)

# Déduction du répertoire JUCE_PROJ
$ScriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
$JUCE_PROJ = Split-Path $ScriptDir -Parent
Write-Host ""
Write-Host "Répertoire JUCE_PROJ détecté : $JUCE_PROJ"
Write-Host ""

# Paramètres
$TemplateName = "Template"
$TemplateRepo = "https://gricad-gitlab.univ-grenoble-alpes.fr/faurefre/juce_template.git"
$SourceDir = Join-Path $JUCE_PROJ $TemplateName
$DestDir = Join-Path $JUCE_PROJ $NewProjectName

# Vérifie que le projet n'existe pas déjà
if (Test-Path $DestDir) {
    Write-Host "Erreur : le dossier cible existe déjà : $DestDir"
    exit 1
}

# Clonage si nécessaire
if (-not (Test-Path $SourceDir)) {
    Write-Host "Template introuvable localement. Clonage depuis GitLab..."
    Set-Location $JUCE_PROJ
    git clone $TemplateRepo $TemplateName
}

# Copie du template
Write-Host "Copie du template vers $NewProjectName..."
Copy-Item -Recurse -Path $SourceDir -Destination $DestDir

# Initialisation Git
Set-Location $DestDir
if (-not (Test-Path ".git")) {
    git init | Out-Null
}

# Création du .gitignore
@"
build/
cmake-build-*/
CMakeFiles/
Makefile
CMakeCache.txt
install_manifest.txt
Builds/
JuceLibraryCode/
*.o
*.so
*.dylib
*.exe
*.app
*.a
.vscode/
.idea/
.DS_Store
*.tar.gz
*.deb
*.pkg
"@ | Set-Content ".gitignore"

git add .gitignore

# Message final
Write-Host ""
Write-Host "Nouveau projet prêt : $DestDir"
Write-Host "Vous pouvez maintenant exécuter :"
Write-Host "cd `"$DestDir`""
Write-Host ".\\2_build.ps1 puis .\\3_exec.ps1"
