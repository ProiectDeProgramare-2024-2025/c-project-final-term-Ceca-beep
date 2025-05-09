#include <stdio.h>
#include <stdlib.h> // for system("clear");

// Cross-platform screen clear
#ifdef _WIN32
    #define CLEAR_SCREEN "cls"
#else
    #define CLEAR_SCREEN "clear"
#endif

#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN    "\033[1;36m"
#define RESET   "\033[0m"


int increment = 0, inc = 0, inc2 = 0;
int increment2 = 0;

int len = 6, len_h = 6;

struct Property {
    float price;
    int rooms;
    int bathrooms;
    int kitchens;
    int parking_space;
};

struct Property app[6];
struct Property boughts[6];
struct Property fav[6];

struct Property2 {
    float price;
    int rooms;
    int bathrooms;
    int kitchens;
    int yard_size;
};

struct Property2 house[6];
struct Property2 boughts_houses[6];
struct Property2 fav_houses[6];

int get_valid_int(int min, int max) {
    int value, result;
    while (1) {
        result = scanf("%d", &value);
        if (result != 1 || value < min || value > max) {
            printf("Invalid input. Please enter a number between %d and %d: ", min, max);
            while (getchar() != '\n');
        } else {
            break;
        }
    }
    return value;
}

void read_f(const char *filename) {
    FILE *filep = fopen(filename, "r");
    if (!filep) {
        perror("Error opening input file");
        exit(1);
    }

    fscanf(filep, "%d %d", &len, &len_h); 

    for (int i = 0; i < len; i++) {
        fscanf(filep, "%f %d %d %d %d",
              &app[i].price, &app[i].rooms, &app[i].bathrooms,
              &app[i].kitchens, &app[i].parking_space);
    }

    for (int i = 0; i < len_h; i++) {
        fscanf(filep, "%f %d %d %d %d",
              &house[i].price, &house[i].rooms, &house[i].bathrooms,
              &house[i].kitchens, &house[i].yard_size);
    }

    fclose(filep);
}

void write_f(const char *filename) {
    FILE *filep = fopen(filename, "w");
    if (!filep) {
        perror("Error opening output file");
        exit(1);
    }

    fprintf(filep, "%d %d\n", len, len_h);

    for (int i = 0; i < len; i++) {
        fprintf(filep, "%.3f %d %d %d %d\n",
                app[i].price, app[i].rooms, app[i].bathrooms,
                app[i].kitchens, app[i].parking_space);
    }

    for (int i = 0; i < len_h; i++) {
        fprintf(filep, "%.3f %d %d %d %d\n",
                house[i].price, house[i].rooms, house[i].bathrooms,
                house[i].kitchens, house[i].yard_size);
    }

    fclose(filep);
}

void header() {
    printf(CYAN "WELCOME TO OUR SALES\n" RESET);
    printf(YELLOW "1-View List\n2-Favourite\n3-Bought\n4-Exit\n" RESET);
}


void header2() {
    printf("1-Apartments\n");
    printf("2-Houses\n");
    printf("3-Go Back\n");
}

void header_app() {
    system(CLEAR_SCREEN);
    for (int i = 0; i < len; i++) {
        printf("%d-Apartment %d\n", i + 1, i + 1);
    }
}

void header_h() {
    system(CLEAR_SCREEN);
    for (int i = 0; i < len_h; i++) {
        printf("%d-House %d\n", i + 1, i + 1);
    }
}

void remove_p(int value) {
    for (int i = value - 1; i < len - 1; i++) {
        app[i] = app[i + 1];
    }
    len--;
}

void remove_house(int value) {
    for (int i = value - 1; i < len_h - 1; i++) {
        house[i] = house[i + 1];
    }
    len_h--;
}

void remove_f(int value) {
    for (int i = value - 1; i < increment2 - 1; i++) {
        fav[i] = fav[i + 1];
    }
    increment2--;
}

void remove_fav_house(int value) {
    for (int i = value - 1; i < inc2 - 1; i++) {
        fav_houses[i] = fav_houses[i + 1];
    }
    inc2--;
}

void add_fav(int value) {
    if (increment2 < 6) {
        fav[increment2] = app[value - 1];
        increment2++;
    } else {
        printf("Favourites list full!\n");
    }
}

void add_fav_house(int value) {
    if (inc2 < 6) {
        fav_houses[inc2] = house[value - 1];
        inc2++;
    } else {
        printf("Favourites list full!\n");
    }
}

void add(int value) {
    if (increment < 6) {
        boughts[increment] = app[value - 1];
        increment++;
    } else {
        printf("Bought list full!\n");
    }
}

void add_house(int value) {
    if (inc < 6) {
        boughts_houses[inc] = house[value - 1];
        inc++;
    } else {
        printf("Bought list full!\n");
    }
}

void print_property_apartment(struct Property p) {
    printf(GREEN "Price: $%.3f\n" RESET, p.price);
    printf("Rooms: %d\n", p.rooms);
    printf("Bathrooms: %d\n", p.bathrooms);
    printf("Kitchens: %d\n", p.kitchens);
    printf("Parking: %s\n", p.parking_space ? "Yes" : "No");
    printf("------------------------\n");
}


void print_property_house(struct Property2 h) {
    printf("Price: $%.3f\n", h.price);
    printf("Rooms: %d\n", h.rooms);
    printf("Bathrooms: %d\n", h.bathrooms);
    printf("Kitchens: %d\n", h.kitchens);
    printf("Yard size: %d sqm\n", h.yard_size);
    printf("------------------------\n");
}

void list_of_fav() {
    for (int i = 0; i < increment2; i++) {
        printf("Apartment %d:\n", i + 1);
        print_property_apartment(fav[i]);
    }
    for (int i = 0; i < inc2; i++) {
        printf("House %d:\n", i + 1);
        print_property_house(fav_houses[i]);
    }
}

int apartment() {
    header_app();
    printf("Select an apartment: ");
    int i = get_valid_int(1, len);
    system(CLEAR_SCREEN);
    printf("Property %d:\n", i);
    print_property_apartment(app[i - 1]);
    return i;
}

int houses() {
    header_h();
    printf("Select a house: ");
    int i = get_valid_int(1, len_h);
    system(CLEAR_SCREEN);
    printf("House %d:\n", i);
    print_property_house(house[i - 1]);
    return i;
}

void to_buy(int option) {
    int value;
    switch (option) {
    case 1:
        value = apartment();
        printf("Do you want to buy this property?\n");
        printf("1 - YES | 2 - NO | 3 - Add to Favourites\n");
        int op = get_valid_int(1, 3);
        switch (op) {
        case 1:
            add(value);
            remove_p(value);
            write_f("input.txt");
            break;
        case 3:
            add_fav(value);
            break;
        }
        break;
    case 2:
        value = houses();
        printf("Do you want to buy this property?\n");
        printf("1 - YES | 2 - NO | 3 - Add to Favourites\n");
        int op2 = get_valid_int(1, 3);
        switch (op2) {
        case 1:
            add_house(value);
            remove_house(value);
            write_f("input.txt");
            break;
        case 3:
            add_fav_house(value);
            break;
        }
        break;
    }
}

void submeniu() {
    int option;
    do {
        system(CLEAR_SCREEN);
        header2();
        printf(BLUE "Enter your option: " RESET);
        option = get_valid_int(1, 3);
        to_buy(option);
    } while (option > 0 && option <= 2);
}

void meniu(int option) {
    switch (option) {
    case 1:
        submeniu();
        break;
    case 2:
        system(CLEAR_SCREEN);
        list_of_fav();
        break;
    case 3:
        system(CLEAR_SCREEN);
        printf("Bought properties:\n");
        for (int i = 0; i < increment; i++) {
            printf("Apartment %d:\n", i + 1);
            print_property_apartment(boughts[i]);
        }
        for (int i = 0; i < inc; i++) {
            printf("House %d:\n", i + 1);
            print_property_house(boughts_houses[i]);
        }
        break;
    }
}

int main() {
    read_f("input.txt");
    int option;
    do {
        system(CLEAR_SCREEN);
        header();
        printf("Enter your option: ");
        option = get_valid_int(1, 4);
        if (option != 4) {
            meniu(option);
            printf("\nPress Enter to Go Back!");
            getchar();
            getchar();
        }
    } while (option > 0 && option <= 3);
}
