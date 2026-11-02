param(
    [Parameter(Mandatory = $true)]
    [string] $RascExe
)

$ErrorActionPreference = "Stop"
$bspRoot = $PSScriptRoot
$solutionPath = Join-Path $bspRoot "solution.xml"
$cpu0Bundle = Join-Path $bspRoot "m85\Objects\template.sbd"
$cpu1Bundle = Join-Path $bspRoot "m33\Objects\template.sbd"
$secureXmlPath = Join-Path $bspRoot ".secure_xml"
$secureAzonePath = Join-Path $bspRoot ".secure_azone"
$secureRzonePath = Join-Path $bspRoot ".secure_rzone"
$outputPath = Join-Path $bspRoot "build\ra8p1_titan_dualcore.sbd"

Add-Type -AssemblyName System.IO.Compression.FileSystem

function Save-XmlDocument
{
    param(
        [System.Xml.XmlDocument] $Document,
        [string] $Path
    )

    $settings = New-Object System.Xml.XmlWriterSettings
    $settings.Encoding = New-Object System.Text.UTF8Encoding($false)
    $settings.Indent = $true
    $settings.NewLineChars = "`r`n"
    $writer = [System.Xml.XmlWriter]::Create($Path, $settings)
    try
    {
        $Document.Save($writer)
    }
    finally
    {
        $writer.Dispose()
    }
}

function Assert-SmartBundle
{
    param(
        [string] $Path,
        [string] $ExpectedCore,
        [string] $ExpectedTarget,
        [string] $ExpectedFspVersion
    )

    $archive = [System.IO.Compression.ZipFile]::OpenRead($Path)
    try
    {
        $entry = $archive.GetEntry("cfg/secure.xml")
        if ($null -eq $entry)
        {
            throw "Smart Bundle '$Path' does not contain cfg/secure.xml."
        }
        $stream = $entry.Open()
        $reader = New-Object System.IO.StreamReader($stream)
        try
        {
            [xml] $configuration = $reader.ReadToEnd()
        }
        finally
        {
            $reader.Dispose()
            $stream.Dispose()
        }

        $settings = $configuration.raConfiguration.generalSettings.option
        $core = ($settings | Where-Object key -eq "Core").value
        $target = ($settings | Where-Object key -eq "#TargetName#").value
        $fspVersion = ($settings | Where-Object key -eq "#FSPVersion#").value
        if ($core -ne $ExpectedCore -or $target -ne $ExpectedTarget -or $fspVersion -ne $ExpectedFspVersion)
        {
            throw "Smart Bundle '$Path' is $core/$target/FSP $fspVersion; expected $ExpectedCore/$ExpectedTarget/FSP $ExpectedFspVersion."
        }
    }
    finally
    {
        $archive.Dispose()
    }
}

if (-not (Test-Path -LiteralPath $cpu0Bundle))
{
    throw "CPU0 Smart Bundle '$cpu0Bundle' does not exist. Build the m85 Keil project first."
}

if (-not (Test-Path -LiteralPath $cpu1Bundle))
{
    throw "CPU1 Smart Bundle '$cpu1Bundle' does not exist. Build the m33 Keil project first."
}

[xml] $solution = Get-Content -Raw -LiteralPath $solutionPath
$targetName = ($solution.raSolution.generalSettings.option | Where-Object key -eq "#TargetName#").value
$fspVersion = ($solution.raSolution.generalSettings.option | Where-Object key -eq "#FSPVersion#").value
Assert-SmartBundle -Path $cpu0Bundle -ExpectedCore "CPU0" -ExpectedTarget $targetName -ExpectedFspVersion $fspVersion
Assert-SmartBundle -Path $cpu1Bundle -ExpectedCore "CPU1" -ExpectedTarget $targetName -ExpectedFspVersion $fspVersion

$secureXml = New-Object System.Xml.XmlDocument
$null = $secureXml.AppendChild($secureXml.CreateXmlDeclaration("1.0", "UTF-8", "no"))
$secureSolution = $secureXml.CreateElement("raSolution")
$secureSolution.SetAttribute("version", "12")
$null = $secureXml.AppendChild($secureSolution)
$null = $secureSolution.AppendChild($secureXml.ImportNode($solution.raSolution.generalSettings, $true))

$secureAzone = New-Object System.Xml.XmlDocument
$null = $secureAzone.AppendChild($secureAzone.CreateXmlDeclaration("1.0", "UTF-8", "yes"))
$azone = $secureAzone.CreateElement("azone")
$null = $secureAzone.AppendChild($azone)
$rzone = $secureAzone.CreateElement("rzone")
$rzone.SetAttribute("name", "$targetName.rzone")
$null = $azone.AppendChild($rzone)
$partition = $secureAzone.CreateElement("partition")
$null = $azone.AppendChild($partition)

foreach ($sourceMemory in $solution.raSolution.raPartitions.memory)
{
    $memory = $secureAzone.CreateElement("memory")
    foreach ($attributeName in @("parent", "name", "size", "offset", "security", "Pname"))
    {
        $memory.SetAttribute($attributeName, $sourceMemory.$attributeName)
    }
    if ($sourceMemory.userDefined -eq "true")
    {
        $memory.SetAttribute("info", "@user")
    }
    $null = $partition.AppendChild($memory)
}

$archive = [System.IO.Compression.ZipFile]::OpenRead($cpu0Bundle)
try
{
    $entry = $archive.GetEntry("cfg/$targetName.rzone")
    if ($null -eq $entry)
    {
        throw "Device resource '$targetName.rzone' is missing from '$cpu0Bundle'."
    }
    $inputStream = $entry.Open()
    $outputStream = [System.IO.File]::Create($secureRzonePath)
    try
    {
        $inputStream.CopyTo($outputStream)
    }
    finally
    {
        $outputStream.Dispose()
        $inputStream.Dispose()
    }
}
finally
{
    $archive.Dispose()
}

try
{
    Save-XmlDocument -Document $secureXml -Path $secureXmlPath
    Save-XmlDocument -Document $secureAzone -Path $secureAzonePath
    & $RascExe -nosplash --launcher.suppressErrors --gensolutionbundle --compiler ARMv6 --devicefamily ra --projectname ra8p1_titan_dualcore $solutionPath
    if ($LASTEXITCODE -ne 0)
    {
        throw "FSP Smart Configurator failed with exit code $LASTEXITCODE."
    }
    if (-not (Test-Path -LiteralPath $outputPath))
    {
        throw "Solution Smart Bundle '$outputPath' was not generated."
    }
    Write-Output "Generated '$outputPath'."
}
finally
{
    Remove-Item -LiteralPath $secureXmlPath, $secureAzonePath, $secureRzonePath -Force -ErrorAction SilentlyContinue
}
