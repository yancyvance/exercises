#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define INPUT_FILE_NAME "data.txt"
#define MAX_NAME_LENGTH 255

// TODO: define two structures here
// the first structure will be called card_t with two components, namely: suit (char) and rank (int)
// the second structure will be called player_t with three components, namely: name (char*), card_count (int), and list_of_cards (card_t*)

// define here



// DO NOT MODIFY THIS PORTION
// function prototypes defined here
// the function definition are located below the main function
player_t *load_file(FILE *, int *);
player_t *create_player_list(int);
void initialize_player(player_t *, char *, int);
void set_player_card_info_at(player_t *, int, char, int);
void process_list_of_players(player_t *, int);
void display_player_information(player_t *);
void print_card_detail(card_t *);
void cleanup(player_t *, int);
void trim_string(char *);



// DO NOT MODIFY THIS PORTION OF THE MAIN FUNCTION
#ifndef MAIN_FUNCTION
int main(void) {
    // read the input file
    FILE *input_file = fopen(INPUT_FILE_NAME, "r");

    // check if the file was opened
    if(input_file == NULL) {
        // if there was a problem, simply return a 1
        printf("There was a problem opening the file. Abort!\n");
        return 1;
    }

    // the number of players indicated in the input file
    // this will be populated by the load_file() function
    int player_count;

    // load the file and pass the address of the player_count variable
    // for it to be populated. Additionally, this function returns a dynamically
    // allocated list of player_t (which we will call list_of_players)
    // it is possible for this function to return NULL if there
    // was a problem (e.g., cannot allocate memory)
    player_t *list_of_players = load_file(input_file, &player_count);

    // close the input file
    fclose(input_file);



    // check if the list was dynamically allocated
    if(list_of_players == NULL) {
        // error; do not proceed
        printf("Unable to dynamically allocate list of player_t. Abort!\n");
        return 2;
    }
    else {
        // indicate that the list was successfully loaded
        printf("Loading Complete.\n");
    }


    // display all the information of the players currently stored in the list
    // this includes the player name, number of cards held, what cards are
    // currently held by each player, and the total of the rank of all the
    // cards held by each player
    process_list_of_players(list_of_players, player_count);


    // perform cleanup by deallocating and freeing all
    // the dynamically allocated spaces in this program
    cleanup(list_of_players, player_count);


    // forget the reference to the memory location
    list_of_players = NULL;


    return 0;
}
// DO NOT MODIFY THIS PORTION OF THE MAIN FUNCTION
#endif


player_t *load_file(FILE *file_ptr, int *count_of_players) {
    // this function will build the list of persons based on the file
    // the address is where we will set the value
    // we can assume that the name will have a maximum of 254 characters
    char name_temp[MAX_NAME_LENGTH];

    // store the number of players into the variable
    // passed to this function by reference
    fscanf(file_ptr, "%d\n", count_of_players);

    // create a dynamic list of players and provide the
    // number of players that needs to be stored
    player_t *list_of_players = create_player_list(*count_of_players);

    // check if the list of players was successfully allocated
    if(list_of_players == NULL) {
        return NULL;
    }

    // process each player from the file
    for(int i = 0; i < *count_of_players; i++) {
        // a pointer to each slot in the list
        // indexed by i
        player_t *p = list_of_players+i;

        // read a line of string which corresponds
        // to the name of the player
        fgets(name_temp, sizeof(name_temp), file_ptr);

        // trim the string because it contains an extra \n
        trim_string(name_temp);

        // read from the file how many cards this player has
        int card_count_temp;
        fscanf(file_ptr, "%d\n", &card_count_temp);

        // initialize the player information and dynamically
        // allocate the list of cards to prepare for storing
        // the card information shortly
        initialize_player(p, name_temp, card_count_temp);


        // read the card information of this player
        // afterward, individually load these information to
        // the list of cards of the player
        char suit_temp;
        int rank_temp;
        for(int j = 0; j < card_count_temp; j++) {
            // read the suit and the rank from the file
            fscanf(file_ptr, "%c%d\n", &suit_temp, &rank_temp);

            // set the information of this card from the list
            // pass the suit and rank information of the card
            // and update the information at that location in
            // the list
            set_player_card_info_at(p, j, suit_temp, rank_temp);
        }

    }

    // return a pointer to the dynamic list of players
    return list_of_players;
}


player_t *create_player_list(int list_count) {
    // TODO: This function accepts the number of slots (count)
    // that needs to be allocated for a dynamic list of players;
    // dynamically allocate a list of players with a given count
    // afterward, it returns the dynamically allocated list
    // in short, it returns a pointer to the list

}


void initialize_player(player_t *player, char *name, int card_count) {
    // TODO: This function accepts a pointer to a player, a string representing
    // the player's name, and the count of cards this player has
    // this function sets the name and the card count of the player
    // additionally, it should dynamically allocate the list of cards
    // of this player given the number of slots

}


void set_player_card_info_at(player_t *player, int card_position, char suit, int rank) {
    // TODO: this function accepts a pointer to a player, the position of the card in the list
    // that needs to be set, the suit and the rank information of that card
    // this will simply set the value of the suit and the rank
    // of the card at a given location in the list of cards of
    // a player; we can assume that the list is already existing
    // and the card_position is valid

    // TODO: Ensure that the suit is in upper case

}


void process_list_of_players(player_t *player_list, int list_count) {
    // TODO: Complete the following function; this function receives
    // a dynamic list of players and the count of players in the list
    // You have to iterate through the list of players
    // and display the information of each player
    // add an extra space in between player information
    // you are required to do a call to display_player_information() here

}


void display_player_information(player_t *player) {
    // TODO: Complete the following function
    // displays information of a single player
    // computation of the total rank should be done here
    // Refer to the following for the formatting requirements

    /*
        Player Name: <name>
        Card Count: <count>
        Card List
        *********
        <S> <R>
        <S> <R>
        Total Rank: <total>
    */

    // the total rank is simply the sum of
    // the rank values of all the cards of the player
    // you are required to do a call to print_card_detail() here

}


void print_card_detail(card_t *card) {
    // TODO: this function accepts a pointer to a card and displays its information
    // It should display the suit of the card followed by a single
    // space then the numerical rank of the card. Format the rank
    // such that it has a width of 2 and is aligned right.
    // For example: C 12 for Club 12
    // D  1 for Diamond 1
    // Lastly, add a newline character at the end

}


void cleanup(player_t *player_list, int list_count) {
    // TODO: this function accepts a dynamic list of players and the count
    // Your task is to complete this function such that it properly deallocates
    // all memory associated with the heap space of type player_t

}


// DO NOT MODIFY THIS PORTION
void trim_string(char *str) {
    // helper function that will remove the extra new line
    // added from reading the input file
    int len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}
