#!/bin/bash

# Convert version number to comparable numeric value
version_to_number() {
    local version="$1"
    local IFS='.'
    local parts=($version)

    # Ensure we have 3 parts
    while [ ${#parts[@]} -lt 3 ]; do
        parts+=(0)
    done

    # Extract X,Y,Z
    local X=${parts[0]}
    local Y=${parts[1]}
    local Z=${parts[2]}

    # Validate each part is a 1-2 digit number
    if ! [[ "$X" =~ ^[0-9]{1,2}$ ]] || ! [[ "$Y" =~ ^[0-9]{1,2}$ ]] || ! [[ "$Z" =~ ^[0-9]{1,2}$ ]]; then
        echo "Error: Invalid version format. Expected X.Y.Z where X/Y/Z are 1-2 digit numbers" >&2
        return 1
    fi

    # Format each part as 2-digit numbers and concatenate
    local number=$(printf "%02d%02d%02d" "$X" "$Y" "$Z")

    # Remove leading zeros to avoid octal interpretation and return the value
    echo $((10#$number))
    return 0
}

RTT_PATH=$(realpath $(dirname $0)/..)
RTT_DOC_PATH=$RTT_PATH/documentation

rm -rf $RTT_DOC_PATH/html

cd $RTT_DOC_PATH

doxygen_version=$(doxygen --version 2>/dev/null)
if [ -z "$doxygen_version" ]; then
    echo "Error: doxygen command not found. Please ensure doxygen is installed." >&2
    exit 1
fi

doxygen_version_number=$(version_to_number "$doxygen_version")
if [ $? -ne 0 ]; then
    echo "Error: Failed to convert version to number!" >&2
    exit 2
fi

if [ $doxygen_version_number -lt 10901 ]; then
    echo "Error: Doxygen version must be at least 1.9.1. Current version is $doxygen_version." >&2
    exit 1
fi

if [ $doxygen_version_number -eq 10901 ]; then
    echo "Info: Doxygen version is 1.9.1" >&2
    config_file="Doxyfile.1.9.1"
elif [ $doxygen_version_number -gt 10901 ] && [ $doxygen_version_number -lt 10908 ]; then
    echo "Info: Doxygen version is greater than 1.9.1 but less than 1.9.8, Using configuration for 1.9.1." >&2
    config_file="Doxyfile.1.9.1"
elif [ $doxygen_version_number -eq 10908 ]; then
    echo "Info: Doxygen version is 1.9.8" >&2
    config_file="Doxyfile.1.9.8"
elif [ $doxygen_version_number -gt 10908 ]; then
    echo "Warning: Doxygen version is greater than 1.9.8. Using configuration for 1.9.8." >&2
    config_file="Doxyfile.1.9.8"
fi

if [ ! -f "$config_file" ]; then
    echo "Error: Configuration file $config_file does not exist." >&2
    exit 3
fi

echo "Running doxygen $doxygen_version with $config_file..."
doxygen "$config_file"
if [ $? -ne 0 ]; then
    echo ""
    echo "OOPS: Something error/warning occurred during Doxygen building, please check it out!"
    echo ""
    exit 1
fi

pushd $RTT_DOC_PATH/html
python3 -m http.server
