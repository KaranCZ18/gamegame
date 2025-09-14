#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Structure for storing scores
struct GameData {
    int userScore;
    int computerScore;
};

// Structure for player choices
struct Choice {
    char option; // 's', 'p', or 'z'
};

// Function to implement the game logic
int game(struct Choice user, struct Choice computer) {
    if (user.option == computer.option)
        return -1; // Draw

    // Winning conditions
    if ((user.option == 's' && computer.option == 'z') ||
        (user.option == 'p' && computer.option == 's') ||
        (user.option == 'z' && computer.option == 'p'))
        return 1; // User wins

    return 0; // Computer wins
}

// Function to display ASCII art for choices
void displayChoice(char choice) {
    switch (choice) {
        case 's':
            printf("   _______\n");
            printf("---'   ____)\n");
            printf("      (_____)\n");
            printf("      (_____)\n");
            printf("      (____)\n");
            printf("---.__(___)\n");
            break;
        case 'p':
            printf("   _______\n");
            printf("---'   ____)____\n");
            printf("          ______)\n");
            printf("          _______)\n");
            printf("         _______)\n");
            printf("---.__________)\n");
            break;
        case 'z':
            printf("   _______\n");
            printf("---'   ____)____\n");
            printf("          ______)\n");
            printf("       __________)\n");
            printf("      (____)\n");
            printf("---.__(___)\n");
            break;
    }
}

// Function to save scores to a file
void save_scores(struct GameData data) {
    FILE *file = fopen("scores.txt", "w");
    if (!file) {
        perror("Error saving scores");
        return;
    }
    fprintf(file, "Your Score=%d Computer Score=%d\n", data.userScore, data.computerScore);
    fclose(file);
}

// Function to load scores from a file
void load_scores(struct GameData *data) {
    FILE *file = fopen("scores.txt", "r");
    if (!file) {
        printf("No previous scores found. Starting fresh!\n");
        data->userScore = 0;
        data->computerScore = 0;
        return;
    }
    fscanf(file, "Your Score=%d Computer Score=%d\n", &data->userScore, &data->computerScore);
    fclose(file);
}

// Main driver code
int main() {
    struct GameData data;
    struct Choice user, computer;
    char playAgain;

    srand(time(NULL));

    // Load previous scores
    load_scores(&data);
    printf("Welcome back! Previous Scores: You = %d, Computer = %d\n", data.userScore, data.computerScore);

    do {
        // Generate computer's choice
        int n = rand() % 100;
        if (n < 33)
            computer.option = 's'; // Stone
        else if (n < 66)
            computer.option = 'p'; // Paper
        else
            computer.option = 'z'; // Scissors

        // Display options
        printf("\nEnter 's' for Stone, 'p' for Paper, 'z' for Scissors: ");
        scanf(" %c", &user.option);

        // Validate input
        if (user.option != 's' && user.option != 'p' && user.option != 'z') {
            printf("Invalid input! Please try again.\n");
            continue;
        }

        // Display choices with ASCII art
        printf("\nYou chose:\n");
        displayChoice(user.option);
        printf("\nComputer chose:\n");
        displayChoice(computer.option);

        // Determine the result
        int result = game(user, computer);
        if (result == -1) {
            printf("\nIt's a Draw!\n");
        } else if (result == 1) {
            printf("\nYou Win!\n");
            data.userScore++;
        } else {
            printf("\nYou Lose!\n");
            data.computerScore++;
        }

        // Display scores
        printf("\nScores: You = %d, Computer = %d\n", data.userScore, data.computerScore);

        // Save scores to file
        save_scores(data);

        // Ask to play again
        printf("\nDo you want to play again? (y/n): ");
        scanf(" %c", &playAgain);

    } while (playAgain == 'y' || playAgain == 'Y');

    // Final scores
    printf("\nFinal Scores: You = %d, Computer = %d\n", data.userScore, data.computerScore);
    printf("Thanks for playing! Your scores have been saved. Goodbye!\n");

    return 0;
}

