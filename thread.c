#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

// Function to calculate square of a number
int calculateSquare(int num) {
    return num * num;
}

int main() {
    int num = 5;
    const int NUM_PROCESSES = 3;
    
    for (int i = 0; i < NUM_PROCESSES; ++i) {
        pid_t pid = fork();

        if (pid == 0) { // Child process
            // Each child calculates the square of the number
            int result = calculateSquare(num);
            std::cout << "Child process " << getpid() << " calculated square: " << result << std::endl;
            return 0;
        } else if (pid < 0) { // Error
            std::cerr << "Error creating child process." << std::endl;
            return 1;
        }
    }

    // Parent process
    std::cout << "Parent process " << getpid() << " waiting for child processes to finish." << std::endl;
    
    // Wait for all child processes to finish
    for (int i = 0; i < NUM_PROCESSES; ++i) {
        int status;
        wait(&status);
    }

    std::cout << "All child processes finished." << std::endl;

    return 0;
}

