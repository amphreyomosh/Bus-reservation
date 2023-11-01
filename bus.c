#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>  // For _getch() function

#define MAX_BUSES 30
#define MAX_SEATS 100

struct User {
    char username[20];
    char password[20];
};

struct Seat {
    int seatNumber;
    int isBooked;
};


// Structure to represent a bus
struct Bus {
    char regNumber[20];
    char makeModel[50];
    int year;
    int availableSeats;
};

// Structure to represent a booking
struct Booking {
    char regNumber[20];
    char username[20];
    int seatNumber;
    int price;
};

// Function to display a booking receipt
void displayReceipt(struct Booking booking) {
    printf("\n--- Receipt ---\n");
    printf("Registration Number: %s\n", booking.regNumber);
    printf("Username: %s\n", booking.username);
    printf("Seat Number: %d\n", booking.seatNumber);
    printf("Price: $%d\n", booking.price);
    printf("---------------\n");
}

int main() {
    struct User users[100];
    int userCount = 0;

    struct Bus buses[MAX_BUSES];
    int busCount = 0;

    struct Booking bookings[MAX_BUSES * MAX_SEATS];
    int bookingCount = 0;
    
    struct Seat busSeats[MAX_BUSES][MAX_SEATS];

    printf("Welcome to Simba Bus company.\nCreate an account to log in.\n\n");

    int choice;
    int isAuthenticated = 0;
    
     // Initialize all seats as not booked
    int i;
    for (i = 0; i < MAX_BUSES; i++) {
    	int j;
        for (j = 0; j < MAX_SEATS; j++) {
            busSeats[i][j].seatNumber = j + 1;
            busSeats[i][j].isBooked = 0;
        }
    }

    while (!isAuthenticated) {
        printf("1. Login\n");
        printf("2. Create an account\n");
        printf("3. Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        system("cls");

        switch (choice) {
            case 1: {
                char username[20];
                char password[20];

                printf("Username: ");
                scanf("%s", username);

                printf("Password: ");
                int index = 0;
                char ch;
                while (1) {
                    ch = _getch(); // Get character without echoing it back
                    if (ch == 13) {  // If Enter key is pressed
                        password[index] = '\0'; // Add null terminator to mark the end of the password
                        break;
                    } else if (ch == 8) { // If Backspace is pressed
                        if (index > 0) {
                            printf("\b \b"); // Move cursor back, erase character, move back again
                            index--;
                        }
                    } else {
                        password[index++] = ch;
                        printf("*"); // Print * to show a masked character
                    }
                }

                int i;
                for (i = 0; i < userCount; i++) {
                    if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
                        isAuthenticated = 1;
                        break;
                    }
                }

                if (isAuthenticated) {
                    printf("\nAuthentication successful!\n\n");
                } else {
                    printf("\nAuthentication failed. Please try again.\n\n");
                }
                break;
            }
            case 2: {
                if (userCount < 100) {
                    char username[20];
                    char password[20];

                    printf("Enter a new username: ");
                    scanf("%s", username);

                    // Check if the username already exists
                    int usernameExists = 0;
                    int i;
                    for ( i = 0; i < userCount; i++) {
                        if (strcmp(users[i].username, username) == 0) {
                            usernameExists = 1;
                            break;
                        }
                    }

                    if (usernameExists) {
                        printf("Username already exists. Please choose a different one.\n\n");
                    } else {
                        printf("Enter a new password: ");
                        scanf("%s", password);

                        // Add the new user
                        struct User newUser;
                        strcpy(newUser.username, username);
                        strcpy(newUser.password, password);
                        users[userCount++] = newUser;

                        printf("Account created successfully!\n\n");
                    }
                } else {
                    printf("Maximum number of users reached. Cannot create more accounts.\n");
                }
                break;
            }
            case 3: {
                printf("Exiting the program.\n");
                return 0;
            }
            default:
                printf("Invalid choice. Please try again.\n\n");
                break;
        }
    }

    // After successful login, allow access to bus information management and booking
    int loggedInChoice;
    while (isAuthenticated) {
        printf("1. Add a new bus record\n");
        printf("2. Display all bus records\n");
        printf("3. Search for a bus by registration number\n");
        printf("4. Book a seat\n");
        printf("5. View available seats\n");
        printf("6. Cancel booking\n");
        printf("7. Logout\n\n");
        printf("Enter your choice: ");
        scanf("%d", &loggedInChoice);
        system("cls");

        switch (loggedInChoice) {
            case 1: {
                if (busCount < MAX_BUSES) {
                    struct Bus newBus;

                    printf("Enter Registration Number: ");
                    scanf("%s", newBus.regNumber);
                    printf("Enter Make and Model: ");
                    scanf(" %[^\n]s", newBus.makeModel);
                    printf("Enter Year: ");
                    scanf("%d", &newBus.year);
                    newBus.availableSeats = MAX_SEATS; // Initialize available seats

                    buses[busCount++] = newBus;

                    printf("Bus record added successfully!\n");
                } else {
                    printf("Maximum number of bus records reached. Cannot add more.\n");
                }
                break;
            }
            case 2: {
                if (busCount > 0) {
                    printf("\nBus Records:\n");
                    int i;
                    for ( i = 0; i < busCount; i++) {
                        printf("Registration Number: %s\n", buses[i].regNumber);
                        printf("Make and Model: %s\n", buses[i].makeModel);
                        printf("Year: %d\n", buses[i].year);
                        printf("Available Seats: %d\n\n", buses[i].availableSeats);
                    }
                } else {
                    printf("No bus records to display.\n");
                }
                break;
            }
            case 3: {
                if (busCount > 0) {
                    char searchRegNumber[20];
                    int found = 0;

                    printf("Enter Registration Number to search: ");
                    scanf("%s", searchRegNumber);
                    int i;
                    for (i = 0; i < busCount; i++) {
                        if (strcmp(buses[i].regNumber, searchRegNumber) == 0) {
                            printf("Bus Found:\n");
                            printf("Registration Number: %s\n", buses[i].regNumber);
                            printf("Make and Model: %s\n", buses[i].makeModel);
                            printf("Year: %d\n", buses[i].year);
                            printf("Available Seats: %d\n\n", buses[i].availableSeats);
                            found = 1;
                            break;
                        }
                    }

                    if (!found) {
                        printf("Bus not found with the provided registration number.\n\n");
                    }
                } else {
                    printf("No bus records to search.\n");
                }
                break;
            }
            case 4: {
                if (busCount > 0) {
                    char searchRegNumber[20];
                    int found = 0;

                    printf("Enter Registration Number to book a seat: ");
                    scanf("%s", searchRegNumber);
                    int i;
  
                    for ( i = 0; i < busCount; i++) {
                        if (strcmp(buses[i].regNumber, searchRegNumber) == 0) {
                            if (buses[i].availableSeats > 0) {
                                char username[20];
                                printf("Simba Bus Company.\n\nBooking.\n\nEnter your username: ");
                                scanf("%s", username);

                                struct Booking newBooking;
                                strcpy(newBooking.regNumber, searchRegNumber);
                                strcpy(newBooking.username, username);
                                newBooking.seatNumber = MAX_SEATS - buses[i].availableSeats + 1;
                                newBooking.price = 1200 ; // Set the price for the seat

                                // Reduce available seats and add the booking
                                buses[i].availableSeats--;
                                bookings[bookingCount++] = newBooking;

                                printf("Seat booked successfully! Your seat number is %d. Journey mercies!\n\n", newBooking.seatNumber);

                                // Display the booking receipt
                                displayReceipt(newBooking);
                            } else {
                                printf("No available seats for this bus, kindly select book another bus.\n");
                            }

                            found = 1;
                            break;
                        }
                    }

                    if (!found) {
                        printf("Bus not found with the provided registration number.\n");
                    }
                } else {
                    printf("No bus records available to book a seat.\n");
                }
                break;
            }
            case 5: {
              if (busCount > 0) {
               char searchRegNumber[20];
               int found = 0;

               printf("Enter Registration Number to view available seats: ");
              scanf("%s", searchRegNumber);
             int i;

            for (i = 0; i < busCount; i++) {
            if (strcmp(buses[i].regNumber, searchRegNumber) == 0) {
                printf("Available seats for %s:\n", searchRegNumber);
                
                int seatsInRow = 5;
                int seatCount = 0;
				int j;
                for (j = 0; j < MAX_SEATS; j++) {
                    if (seatCount % seatsInRow == 0) {
                        printf("\n");
                    }
                    if (seatCount % seatsInRow != 2) {
                        if (!busSeats[i][j].isBooked) {
                            printf("|  %2d  |", busSeats[i][j].seatNumber);
                        } else {
                            printf("|  XX  |"); // XX to represent booked seats
                        }
                    } else {
                        printf("|      |"); // Leave the third column empty
                    }
                    seatCount++;
                }
                found = 1;
                printf("\n");
                break;
            }
        }

            if (!found) {
            printf("Bus not found with the provided registration number.\n");
            }
        } else {
        printf("No bus records available to view available seats.\n");
       }
             break;
    }


            case 6: {
                // Cancel booking
                char searchRegNumber[20];
                int seatNumber;
                int found = 0;

                printf("Enter Registration Number to cancel booking: ");
                scanf("%s", searchRegNumber);

                printf("Enter your seat number: ");
                scanf("%d", &seatNumber);
                int i;

                for (i = 0; i < bookingCount; i++) {
                    if (strcmp(bookings[i].regNumber, searchRegNumber) == 0 && bookings[i].seatNumber == seatNumber) {
                        // Increase available seats and remove the booking
                        int j;
                        for ( j = 0; j < busCount; j++) {
                            if (strcmp(buses[j].regNumber, searchRegNumber) == 0) {
                                buses[j].availableSeats++;
                                break;
                            }
                        }
                        int i;

                        for (j = i; j < bookingCount - 1; j++) {
                            bookings[j] = bookings[j + 1];
                        }
                        bookingCount--;

                        printf("Booking canceled successfully!\n");
                        found = 1;
                        break;
                    }
                }

                if (!found) {
                    printf("Booking not found with the provided registration number and seat number.\n");
                }
                break;
            }
            case 7: {
                printf("Logging out...\n");
                isAuthenticated = 0;
                break;
            }
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }

    return 0;
}
