#include <stdio.h>
#include <string.h>

#define MAX_ROOMS 10
#define SINGLE_ROOM_PRICE 1000
#define DOUBLE_ROOM_PRICE 1500
#define SUITE_ROOM_PRICE 2000

// Structure to represent each room's information
typedef struct {
    int roomNumber;
    char customerName[50];
    int isBooked;
    int roomType; // 1 - Single, 2 - Double, 3 - Suite
    int daysBooked;
} Room;

Room hotel[MAX_ROOMS];

// Function to initialize all rooms
void initializeRooms() {
    for (int i = 0; i < MAX_ROOMS; i++) {
        hotel[i].roomNumber = i + 1;
        hotel[i].isBooked = 0;
        hotel[i].roomType = 0;
        hotel[i].daysBooked = 0;
        strcpy(hotel[i].customerName, "");
    }
}

// Function to display all available rooms
void displayAvailableRooms() {
    printf("\nAvailable Rooms:\n");
    int found = 0;
    for (int i = 0; i < MAX_ROOMS; i++) {
        if (hotel[i].isBooked == 0) {
            printf("Room %d is available.\n", hotel[i].roomNumber);
            found = 1;
        }
    }
    if (!found) {
        printf("No rooms available.\n");
    }
}

// Function to display all booked rooms
void displayBookedRooms() {
    printf("\nBooked Rooms:\n");
    int found = 0;
    for (int i = 0; i < MAX_ROOMS; i++) {
        if (hotel[i].isBooked == 1) {
            char *type;
            switch (hotel[i].roomType) {
                case 1: type = "Single"; break;
                case 2: type = "Double"; break;
                case 3: type = "Suite"; break;
                default: type = "Unknown"; break;
            }
            int cost = 0;
            if (hotel[i].roomType == 1)
                cost = SINGLE_ROOM_PRICE * hotel[i].daysBooked;
            else if (hotel[i].roomType == 2)
                cost = DOUBLE_ROOM_PRICE * hotel[i].daysBooked;
            else if (hotel[i].roomType == 3)
                cost = SUITE_ROOM_PRICE * hotel[i].daysBooked;

            printf("Room %d - Booked by %s (%s Room for %d day(s)) - Total Cost: $%d\n",
                   hotel[i].roomNumber, hotel[i].customerName, type,
                   hotel[i].daysBooked, cost);
            found = 1;
        }
    }
    if (!found) {
        printf("No rooms are currently booked.\n");
    }
}

// Function to book a room
void bookRoom() {
    int roomNum;
    char name[50];
    int roomType;
    int numberOfDays;
    int totalCost;

    printf("\nEnter room number to book (1-%d): ", MAX_ROOMS);
    scanf("%d", &roomNum);
    getchar(); // Clear newline

    if (roomNum < 1 || roomNum > MAX_ROOMS) {
        printf("Invalid room number!\n");
        return;
    }

    if (hotel[roomNum - 1].isBooked) {
        printf("Room %d is already booked!\n", roomNum);
        return;
    }

    printf("Enter customer name: ");
    scanf("%s",name);

    // Choose room type
    printf("Choose Room Type:\n");
    printf("1. Single Room (1000 per night)\n");
    printf("2. Double Room (1500 per night)\n");
    printf("3. Suite Room (2000 per night)\n");
    printf("Enter your choice: ");
    scanf("%d", &roomType);

    if (roomType < 1 || roomType > 3) {
        printf("Invalid room type selected!\n");
        return;
    }

    printf("Enter number of days to book: ");
    scanf("%d", &numberOfDays);

    if (numberOfDays <= 0) {
        printf("Invalid number of days!\n");
        return;
    }

    // Calculate total cost
    if (roomType == 1)
        totalCost = SINGLE_ROOM_PRICE * numberOfDays;
    else if (roomType == 2)
        totalCost = DOUBLE_ROOM_PRICE * numberOfDays;
    else
        totalCost = SUITE_ROOM_PRICE * numberOfDays;

    // Save booking info
    hotel[roomNum - 1].isBooked = 1;
    hotel[roomNum - 1].roomType = roomType;
    hotel[roomNum - 1].daysBooked = numberOfDays;
    strcpy(hotel[roomNum - 1].customerName, name);

    printf("Room %d booked successfully for %s.\n", roomNum, name);
    printf("Total cost for booking: %d\n", totalCost);
    printf("Thank you for booking with us!\n");
}

// Function to cancel a booking
void cancelBooking() {
    int roomNum;
    printf("\nEnter room number to cancel booking (1-%d): ", MAX_ROOMS);
    scanf("%d", &roomNum);

    if (roomNum < 1 || roomNum > MAX_ROOMS) {
        printf("Invalid room number!\n");
        return;
    }

    if (hotel[roomNum - 1].isBooked == 0) {
        printf("Room %d is not currently booked.\n", roomNum);
        return;
    }

    hotel[roomNum - 1].isBooked = 0;
    hotel[roomNum - 1].roomType = 0;
    hotel[roomNum - 1].daysBooked = 0;
    strcpy(hotel[roomNum - 1].customerName, "");
    printf("Booking for Room %d has been successfully cancelled.\n", roomNum);
}

int main() {
    int choice;
    initializeRooms();

    while (1) {
        printf("\nHotel Room Booking System\n");
        printf("1. View Available Rooms\n");
        printf("2. Book a Room\n");
        printf("3. View Booked Rooms\n");
        printf("4. Cancel a Booking\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayAvailableRooms();
                break;
            case 2:
                bookRoom();
                break;
            case 3:
                displayBookedRooms();
                break;
            case 4:
                cancelBooking();
                break;
            case 5:
                printf("Exiting program...\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
