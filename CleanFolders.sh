#!/bin/bash

# Define the folders to search for
foldersToDelete=("logs" "bin" "obj" ".vs" ".idea" ".vscode" ".pio")

# Function to delete folders
delete_folders() {
    local folderNames=("$@")
    
    for folderName in "${folderNames[@]}"; do
        echo "Searching and deleting '$folderName' folders..."
        
        # Find and delete directories
        find . -type d -name "$folderName" -exec bash -c '
            for dir; do
                if rm -rf "$dir"; then
                    echo -e "\033[32mDeleted folder: $dir\033[0m"
                else
                    echo -e "\033[31mFailed to delete folder: $dir\033[0m"
                fi
            done
        ' bash {} +
    done
}

# Call the function
delete_folders "${foldersToDelete[@]}"
