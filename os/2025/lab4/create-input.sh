#!/bin/bash

# Get user inputs
read -p "Enter the number of lines to generate: " NUM_LINES
read -p "Enter the output filename: " OUTPUT_FILE

# Define headers
echo "ID Image_Name Name IP_Address Date Username System_Load CPU_Usage Memory_Usage Disk_Space" > "$OUTPUT_FILE"

# Function to generate random IP
random_ip() {
    echo "$((RANDOM % 256)).$((RANDOM % 256)).$((RANDOM % 256)).$((RANDOM % 256))"
}

# Function to generate a random Docker-like image name
random_docker_image() {
    ADJECTIVES=("bold" "clever" "daring" "eager" "fierce" "gentle" "happy" "jolly" "keen" "lucky")
    ANIMALS=("albatross" "beaver" "cougar" "dolphin" "elephant" "falcon" "giraffe" "hippo" "iguana" "jaguar")
    echo "${ADJECTIVES[RANDOM % ${#ADJECTIVES[@]}]}_${ANIMALS[RANDOM % ${#ANIMALS[@]}]}:$((RANDOM % 10 + 1)).$((RANDOM % 10))"
}

# Generate data
for ((i=1; i<=NUM_LINES; i++)); do
    ID="$i"
    IMAGE_NAME=$(random_docker_image)
    NAME="User_$i"
    IP_ADDRESS=$(random_ip)
    DATE=$(date "+%Y-%m-%d %H:%M:%S")
    USERNAME="user$i"
    SYSTEM_LOAD="$((RANDOM % 500))"
    SYSTEM_LOAD="$(echo ${SYSTEM_LOAD:0:1}.${SYSTEM_LOAD:1})"
    CPU_USAGE="$((RANDOM % 101))%"
    MEMORY_USAGE="$((RANDOM % 101))%"
    DISK_SPACE="$((RANDOM % 101))%"
    
    # Append data to file
    echo "$ID $IMAGE_NAME $NAME $IP_ADDRESS $DATE $USERNAME $SYSTEM_LOAD $CPU_USAGE $MEMORY_USAGE $DISK_SPACE" >> "$OUTPUT_FILE"
done

echo "Data generation complete. Output saved in $OUTPUT_FILE."
