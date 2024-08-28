#define STB_IMAGE_IMPLEMENTATION
#include "./stb/stb_image.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to map a byte to a character
char byte_to_char(unsigned char byte) {
    // Define a character set for the password (e.g., alphanumeric)
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    size_t charset_size = sizeof(charset) - 1;

    // Map the byte to an index in the charset
    return charset[byte % charset_size];
}

// Function to generate a password from image data
void generate_password(const unsigned char *img, int img_size, unsigned int seed, int password_length) {
    // Seed the random number generator
    srand(seed);

    printf("Generated password: ");
    for (int i = 0; i < password_length; i++) {
        // Use a semi-random index based on the image data and seed
        int random_index = rand() % img_size;
        char password_char = byte_to_char(img[random_index]);
        printf("%c", password_char);
    }
    printf("\n");
}

int main() {
    // Define buffer size for the file path
    char path[256];

    unsigned int seed;
    int password_length;

    // Get the image path
    printf("Enter the path of the image: ");
    fgets(path, sizeof(path), stdin);

    // Remove the newline character from the input path if it exists
    size_t len = strlen(path);
    if (len > 0 && path[len-1] == '\n') {
        path[len-1] = '\0';
    }

    // Get the seed
    printf("Enter the seed: ");
    scanf("%u", &seed);

    // Get the desired password length
    printf("Enter the password length: ");
    scanf("%d", &password_length);

    // Load the image
    int width, height, channels;
    unsigned char *img = stbi_load(path, &width, &height, &channels, 0);

    if (img == NULL) {
        printf("Error in loading the image\n");
        return 1;
    }

    // Calculate the size of the image data in bytes
    int img_size = width * height * channels;

    // Generate the password
    generate_password(img, img_size, seed, password_length);

    // Free the image memory
    stbi_image_free(img);

    return 0;
}
