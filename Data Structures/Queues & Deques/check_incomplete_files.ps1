# PowerShell script to identify incomplete README files (less than 1000 characters)

Write-Host "🔍 Checking for incomplete README files..." -ForegroundColor Yellow
Write-Host "Threshold: Files with less than 1000 characters" -ForegroundColor Gray
Write-Host ""

# Get all README.md files recursively
$readmeFiles = Get-ChildItem -Path "." -Filter "*README.md" -Recurse

# Arrays to store results
$incompleteFiles = @()
$completeFiles = @()
$totalFiles = 0

foreach ($file in $readmeFiles) {
    $totalFiles++
    $content = Get-Content -Path $file.FullName -Raw -ErrorAction SilentlyContinue
    
    if ($content) {
        $charCount = $content.Length
        $relativePath = $file.FullName.Replace((Get-Location).Path, "").TrimStart('\')
        
        if ($charCount -lt 1000) {
            $incompleteFiles += [PSCustomObject]@{
                Path = $relativePath
                Characters = $charCount
                Size = "$([math]::Round($charCount/1024, 2)) KB"
            }
        } else {
            $completeFiles += [PSCustomObject]@{
                Path = $relativePath
                Characters = $charCount
                Size = "$([math]::Round($charCount/1024, 2)) KB"
            }
        }
    } else {
        # Empty file
        $relativePath = $file.FullName.Replace((Get-Location).Path, "").TrimStart('\')
        $incompleteFiles += [PSCustomObject]@{
            Path = $relativePath
            Characters = 0
            Size = "0 KB"
        }
    }
}

# Display results
Write-Host "📊 SUMMARY:" -ForegroundColor Cyan
Write-Host "Total README files found: $totalFiles" -ForegroundColor White
Write-Host "Complete files (≥1000 chars): $($completeFiles.Count)" -ForegroundColor Green
Write-Host "Incomplete files (<1000 chars): $($incompleteFiles.Count)" -ForegroundColor Red
Write-Host ""

if ($incompleteFiles.Count -gt 0) {
    Write-Host "🚨 INCOMPLETE FILES THAT NEED WORK:" -ForegroundColor Red
    Write-Host "=" * 60 -ForegroundColor Red
    
    $incompleteFiles | Sort-Object Characters | ForEach-Object {
        $status = if ($_.Characters -eq 0) { "EMPTY" } else { "STUB" }
        Write-Host "[$status] $($_.Path)" -ForegroundColor Red
        Write-Host "  └─ $($_.Characters) characters ($($_.Size))" -ForegroundColor Yellow
    }
    
    Write-Host ""
    Write-Host "📝 INCOMPLETE FILES LIST (for easy copying):" -ForegroundColor Magenta
    Write-Host "-" * 50 -ForegroundColor Magenta
    $incompleteFiles | Sort-Object Path | ForEach-Object {
        Write-Host $_.Path -ForegroundColor White
    }
    
    # Save incomplete files to a text file
    $incompleteFiles | Sort-Object Path | Select-Object -ExpandProperty Path | Out-File -FilePath "incomplete_files_list.txt" -Encoding UTF8
    Write-Host ""
    Write-Host "💾 Incomplete files list saved to: incomplete_files_list.txt" -ForegroundColor Cyan
    
} else {
    Write-Host "🎉 ALL FILES ARE COMPLETE!" -ForegroundColor Green
    Write-Host "All README files have 1000+ characters." -ForegroundColor Green
}

Write-Host ""
Write-Host "✅ COMPLETION STATISTICS:" -ForegroundColor Green
Write-Host "Progress: $($completeFiles.Count)/$totalFiles files complete ($([math]::Round(($completeFiles.Count/$totalFiles)*100, 1))%)" -ForegroundColor White

# Show top 5 largest files for reference
if ($completeFiles.Count -gt 0) {
    Write-Host ""
    Write-Host "📈 TOP 5 LARGEST COMPLETE FILES:" -ForegroundColor Blue
    $completeFiles | Sort-Object Characters -Descending | Select-Object -First 5 | ForEach-Object {
        Write-Host "  $($_.Path) - $($_.Characters) chars" -ForegroundColor Gray
    }
}

# Show smallest incomplete files that need attention first
if ($incompleteFiles.Count -gt 0) {
    Write-Host ""
    Write-Host "⚠️  PRIORITY FILES (smallest/empty first):" -ForegroundColor Yellow
    $incompleteFiles | Sort-Object Characters | Select-Object -First 10 | ForEach-Object {
        $priority = if ($_.Characters -eq 0) { "HIGH" } elseif ($_.Characters -lt 100) { "HIGH" } elseif ($_.Characters -lt 500) { "MEDIUM" } else { "LOW" }
        Write-Host "  [$priority] $($_.Path)" -ForegroundColor $(if ($priority -eq "HIGH") {"Red"} elseif ($priority -eq "MEDIUM") {"Yellow"} else {"White"})
    }
}

Write-Host ""
Write-Host "🔧 Script completed!" -ForegroundColor Green
