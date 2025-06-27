# PowerShell script to create README files for all examples under each pattern

# Define the patterns and their examples
$patterns = @{
    "01-Basic-Queue-Operations" = @(
        "Implement a queue using arrays",
        "Implement a queue using linked lists", 
        "Design a circular queue",
        "Implement queue with stack operations"
    )
    "02-Breadth-First-Search-BFS" = @(
        "Binary tree level order traversal",
        "Graph BFS traversal",
        "Shortest path in unweighted graph",
        "Connected components in graph",
        "Word ladder problem",
        "Rotting oranges problem",
        "Knight's shortest path on chessboard"
    )
    "03-Level-by-Level-Processing" = @(
        "Binary tree zigzag level order traversal",
        "Binary tree right side view",
        "Average of levels in binary tree",
        "Minimum depth of binary tree",
        "Maximum width of binary tree",
        "Populating next right pointers"
    )
    "04-Multi-Source-BFS" = @(
        "Rotting oranges",
        "Walls and gates",
        "01 Matrix (distance to nearest 0)",
        "Pacific Atlantic water flow",
        "Shortest distance from all buildings"
    )
    "05-Sliding-Window-with-Queue" = @(
        "Sliding window maximum",
        "Sliding window minimum",
        "First negative integer in every window",
        "Sum of minimum and maximum elements of all subarrays"
    )
    "06-Task-Scheduling" = @(
        "Task scheduler",
        "Course schedule problems",
        "Alien dictionary",
        "Minimum height trees",
        "Topological sorting"
    )
    "07-State-Space-Search" = @(
        "Open the lock",
        "Word ladder",
        "Minimum genetic mutation",
        "Jump game problems",
        "Water jug problem",
        "8-puzzle problem"
    )
    "08-Island-Connected-Components" = @(
        "Number of islands",
        "Max area of island",
        "Surrounded regions",
        "Pacific Atlantic water flow",
        "Number of distinct islands",
        "Making a large island"
    )
    "09-Queue-with-Special-Properties" = @(
        "Design circular queue",
        "Design hit counter",
        "Moving average from data stream",
        "Design snake game",
        "LRU cache (using queue-like operations)",
        "Design phone directory"
    )
    "10-Matrix-Grid-BFS" = @(
        "Shortest path in binary matrix",
        "As far from land as possible",
        "Shortest bridge",
        "Jump game IV",
        "Minimum knight moves",
        "Cut off trees for golf event"
    )
    "11-Queue-Reconstruction" = @(
        "Queue reconstruction by height",
        "Reveal cards in increasing order",
        "Dota2 senate",
        "Design circular deque"
    )
    "12-Monotonic-Queue" = @(
        "Sliding window maximum",
        "Shortest subarray with sum at least K",
        "Jump game VI",
        "Constrained subsequence sum"
    )
    "13-Producer-Consumer" = @(
        "Design bounded blocking queue",
        "Web crawler multithreading",
        "Print in order problems",
        "Building H2O molecules"
    )
    "14-Simulation" = @(
        "Design hit counter",
        "Logger rate limiter",
        "Time based key-value store",
        "Design phone directory",
        "Design tic-tac-toe game"
    )
    "15-Bidirectional-BFS" = @(
        "Word ladder",
        "Minimum genetic mutation",
        "Open the lock (optimized)"
    )
}

# Function to convert example name to filename
function Convert-ToFileName {
    param($exampleName)
    
    $fileName = $exampleName.ToLower()
    $fileName = $fileName -replace '\s+', '-'          # Replace spaces with hyphens
    $fileName = $fileName -replace '[^\w\-\(\)]', ''   # Remove special chars except hyphens and parentheses
    $fileName = $fileName -replace '\-+', '-'          # Replace multiple hyphens with single
    $fileName = $fileName.Trim('-')                    # Remove leading/trailing hyphens
    
    return "$fileName-README.md"
}

# Function to create README content
function Create-ReadmeContent {
    param($exampleName, $patternName)
    
    $content = @"
# $exampleName

## Problem Description
<!-- Add problem description here -->

## Approach
<!-- Describe the approach and algorithm -->

## Algorithm Steps
1. <!-- Step 1 -->
2. <!-- Step 2 -->
3. <!-- Step 3 -->

## Implementation

### Python
``````python
# Implementation goes here
``````

### Time Complexity
<!-- Add time complexity analysis -->

### Space Complexity
<!-- Add space complexity analysis -->

## Examples

### Example 1
``````
Input: 
Output: 
Explanation: 
``````

### Example 2
``````
Input: 
Output: 
Explanation: 
``````

## Notes
<!-- Add any additional notes, edge cases, or variations -->

## Related Problems
<!-- List related problems -->

## Pattern: $patternName
<!-- Explain how this problem fits the pattern -->
"@
    
    return $content
}

# Create README files for each pattern and example
foreach ($pattern in $patterns.Keys) {
    Write-Host "Creating README files for pattern: $pattern" -ForegroundColor Green
    
    $patternPath = Join-Path (Get-Location) $pattern
    
    # Ensure directory exists
    if (-not (Test-Path $patternPath)) {
        New-Item -ItemType Directory -Path $patternPath -Force | Out-Null
    }
    
    foreach ($example in $patterns[$pattern]) {
        $fileName = Convert-ToFileName $example
        $filePath = Join-Path $patternPath $fileName
        
        # Create README content
        $content = Create-ReadmeContent $example $pattern
        
        # Write to file
        Set-Content -Path $filePath -Value $content -Encoding UTF8
        
        Write-Host "  Created: $fileName" -ForegroundColor Cyan
    }
}

Write-Host "`nAll README files have been created successfully!" -ForegroundColor Yellow
Write-Host "Total patterns: $($patterns.Count)" -ForegroundColor Yellow
Write-Host "Total examples: $(($patterns.Values | ForEach-Object { $_.Count } | Measure-Object -Sum).Sum)" -ForegroundColor Yellow
