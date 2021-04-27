////////////////////////////////////////////////////////////////////////////////
//
//  File           : cmpsc311-f16-assign1.c
//  Description    : This is the main source code for for the first assignment
//                   of CMPSC311 at Penn State University.  See the related
//                   assignment page for details.
//
//   Author        : Trisha Mandal
//   Last Modified : 26th September, 2020
//

// Include Files
#include <stdio.h>
#include <cmpsc311_util.h>

// Defines
#define NUM_CARDS 52
#define MAX_CARDS 11
#define SPADE   "\xE2\x99\xA0"
#define CLUB    "\xE2\x99\xA3"
#define HEART   "\xE2\x99\xA5"
#define DIAMOND "\xE2\x99\xA6"

// Functions

////////////////////////////////////////////////////////////////////////////////
//
// Function     : print_card
// Description  : print the card from the integer value
//
// Inputs       : card - the card to print
// Outputs      : 0 always

int print_card( int card ) {

    // CODE HERE
    char card_faces[] = "234567891JQKA";
    char *card_suits[] = { SPADE, CLUB, HEART, DIAMOND };
    int suit = card / 13, cardty = card % 13;
    if ( cardty == 8 ) {
        printf( "10%s", card_suits[suit] );
    } else {
        printf( "%c%s", card_faces[cardty], card_suits[suit] );
    }

    // Return zero
    return( 0 );
}

////////////////////////////////////////////////////////////////////////////////
//
// Function     : print_cards
// Description  : print a number of cards (no more than 13 on one line)
//
// Inputs       : cards - the array of cards to print
//                num_cards - the number of cards to print
// Outputs      : 0 always

int print_cards( int deck[], int numcards) {

// Here I am using a loop to print out the deck with 13 cards on each row 
    for(int i =0; i<numcards; i++)
        {  
            if(i%13 == 0 && i != 0)
                printf("\n");
            
            print_card(deck[i]);
            printf("  ");
        }
    
}

////////////////////////////////////////////////////////////////////////////////
//
// Function     : shuffle_cards
// Description  : print a number of cards (no more than 13 on one line)
//
// Inputs       : cards - the array of cards to print
//                num_cards - the number of cards to print
// Outputs      : 0 always

int shuffle_cards( int cards[], int num_cards ) {
    // Here i used the Fisher Yates shuffle algorithm to produce the shuffle function
    int temp;
    uint32_t j;
     for (int i = num_cards-1; i>=1; i--)
        {
            j = getRandomValue(0,i);
            temp= cards[i];
            cards[i] = cards[j];
            cards[j] = temp;
        }

     return 0;
}
 

////////////////////////////////////////////////////////////////////////////////
//
// Function     : hand_value
// Description  : return the value of the hand
//
// Inputs       : cards - the array of cards in the hand
//                num_cards - the number of cards in the hand
// Outputs      : 0 always

int hand_value( int cards[], int num_cards ) {
    // Here I am checking how much the hand value is for the cards passed
    int sum = 0;
    // I am checking which value from the deck is passed and the adding the appropriate value of it to the total hand value
    for(int i = 0; i<num_cards; i++)
    {
        if(cards[i] != 12 || cards[i] != 25 ||cards[i] != 38 || cards[i] != 51)
        {  
            if(cards[i] == 0 || cards[i] == 13 ||cards[i] == 26 || cards[i] == 39)
                sum = sum + 2;
            if(cards[i] == 1 || cards[i] == 14 ||cards[i] == 27 || cards[i] == 40)
                sum = sum + 3;
            if(cards[i] == 2 || cards[i] == 15 ||cards[i] == 28 || cards[i] == 41)
                sum = sum + 4;
            if(cards[i] == 3 || cards[i] == 16 ||cards[i] == 29 || cards[i] == 42)
                sum = sum + 5;
            if(cards[i] == 4 || cards[i] == 17 ||cards[i] == 30 || cards[i] == 43)
                sum = sum + 6;
            if(cards[i] == 5 || cards[i] == 18 ||cards[i] == 31 || cards[i] == 44)
                sum = sum + 7;
            if(cards[i] == 6 || cards[i] == 19 ||cards[i] == 32 || cards[i] == 45)
                sum = sum + 8;
            if(cards[i] == 7 || cards[i] == 20 ||cards[i] == 33 || cards[i] == 46)
                sum = sum + 9;
            if(cards[i] == 8 || cards[i] == 21 ||cards[i] == 34 || cards[i] == 47)
                sum = sum + 10;
            if(cards[i] == 9 || cards[i] == 22 ||cards[i] == 35 || cards[i] == 48)
                sum = sum + 10;
            if(cards[i] == 10 || cards[i] == 23 ||cards[i] == 36 || cards[i] == 49)
                sum = sum + 10;
            if(cards[i] ==11 || cards[i] == 24 ||cards[i] == 37 || cards[i] == 50)
                sum = sum + 10;
        }

    }
    // This for loop is checking for the Ace case and what value needs to be added in the hand value
    for(int i =0; i<num_cards; i++)
    {
        if(cards[i] == 12 || cards[i] == 25 ||cards[i] == 38 || cards[i] == 51)
            { 
                if(sum<=10)
                    sum = sum + 11; 
                else
                    sum = sum + 1;
            }
    }
    return sum;
}
 

////////////////////////////////////////////////////////////////////////////////
//
// Function     : sort_cards
// Description  : sort a collection of cards
//
// Inputs       : hand - the cards to sort
//                num_cards - the number of cards in the hand
// Outputs      : 0 always

int sort_cards( int hand[], int num_cards ) {
    // I used the bubble sort algorithm to write the sort_cards function 
    int temp;
    for (int i = 0 ; i < num_cards - 1; i++)
    {
        for (int j = 0 ; j <  num_cards - i - 1; j++)
        {
            if (hand[j] > hand[j+1]) /* For decreasing order use < */
            {
                temp       = hand[j];
                hand[j]   = hand[j+1];
                hand[j+1] = temp;
            }
        }
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
//
// Function     : dealer_play
// Description  : dealer decision to hit or stand (hit on anything less 
//                than 17)
//
// Inputs       : hand - cards dealer has
//                num_cards - the number of cards in player hand
// Outputs      : 0 = stand, 1 = hit

int dealer_play( int hand[], int num_cards ) {
    int totalhandvalue = 0;
    // I am checking is the hand value is less or equal to 16 and only then dealer will hit otherwise he will stand
    totalhandvalue = hand_value(hand, num_cards);
    if(totalhandvalue <=16)
        return 1;
    else
        return 0;

}

////////////////////////////////////////////////////////////////////////////////
//
// Function     : player_play
// Description  : player decision to hit or stand
//
// Inputs       : hand - cards player has
//                num_cards - the number of cards in player hand
//                dealer_card - the dealers face up card
// Outputs      : 0 = stand, 1 = hit

int player_play( int hand[], int num_cards, int dealer_card) {
    int totalhandvalue =0;
    // I am checking is the hand value is less or equal to 10 and dealer card is less than 10 
    // only then player will hit otherwise he will stand
    totalhandvalue= hand_value(hand,num_cards);
    if(totalhandvalue <=10 && dealer_card <10)
        return 1;
    else
        return 0;
    
}

////////////////////////////////////////////////////////////////////////////////
//
// Function     : play_hand
// Description  : play a hand of black jack
//
// Inputs       : deck - the whole deck of cards
//                num_cards - the number of cards in the deck
//                player_money - pointer to player amount of money
// Outputs      : 1 if player wins, 0 if dealer wins

int play_hand( int deck[], int num_cards, float *player_money) {
    // I am checking if the player is broke or not 
    if(*player_money < 5.0f)
        {
            return -1;
        }
    // I am deducting money for the round
    *player_money -= 5.0f;
    for(int i = 0; i<num_cards; i++)
        {
            deck[i] = i;
        }
    shuffle_cards(deck, num_cards);
    int dealercards[MAX_CARDS];
    int playercards[MAX_CARDS];
    int playerhandvalue=0;
    int dealerhandvalue=0;
    // I am dealing two cards for the player and dealer
    dealercards[0] = deck[0];
    dealercards[1] = deck[1];
    playercards[0] = deck[2];
    playercards[1] = deck[3];
    // removing those cards from the deck
    num_cards = num_cards -4;
    for (int c = 0; c < num_cards; c++)
        {
            deck[c] = deck[c+4];
        }

    int numofdealercards =2;
    int numofplayercards =2;
   
    int playerplay=0, dealerplay =0;
    playerhandvalue = hand_value(dealercards, numofdealercards);
    dealerhandvalue = hand_value(dealercards, numofdealercards);
    // print the dealer and player cards
    printf("Dealer cards: ");
    print_card(dealercards[0]);
    printf("  XX");
    printf("\n\n");  

    printf("Player cards: ");
    for(int i = 0; i< numofplayercards; i++)
            {
                print_card(playercards[i]);
                printf("  ");
            }
    printf("\n");  
    // checking is player has blackjack
    if(playerhandvalue==21)
        {
            *player_money += 12.5f;
            printf("\nPlayer has Blackjack!, wins $7.50");
            return 1;

        }
    // checking is player bust
     if(playerhandvalue>21)
        {
            printf("\nPlayer BUSTS...dealer wins!");
            return 0;
        }
    // checking if dealer bust
    if(dealerhandvalue>21)
        {
            *player_money += 10.0f;
            printf("\nDealer BUSTS...player wins!");
            return 1;
        }
    // The player hit and stand cases
    while(playerhandvalue<22)
    {   playerplay = player_play(playercards, numofplayercards, dealercards[0]);
    // checking what the player play is then adding a card if player hit otherwise player stands and final cards are printed out
        if (playerplay == 1)
        {   
            playercards[numofplayercards] = deck[0];
            numofplayercards++;

            num_cards--;
            for (int c = 0; c < num_cards; c++)
                {
                    deck[c] = deck[c+1];
                
                }
            playerhandvalue = hand_value(playercards, numofplayercards);
            printf("Player hits(%d):", playerhandvalue);
            for(int i = 0; i< numofplayercards; i++)
                {
                    print_card(playercards[i]);
                    printf("  ");
                }
            printf("\n");

            if(playerhandvalue==21)
                {
                    *player_money +=  12.5f;
                    printf("\nPlayer has Blackjack!, wins $7.50");
                    return 1;

                }
            if(playerhandvalue>21)
                {
                    printf("\nPlayer BUSTS...dealer wins!");
                    return 0;
                }
        }

        else
        {
            printf("Player stands(%d):", playerhandvalue);
            for(int i = 0; i< numofplayercards; i++)
                {
                    print_card(playercards[i]);
                    printf("  ");
                }
            printf("\n");
            break;
        }
    }
    printf("\n");
    // The dealer hit and stand cases
    while(dealerhandvalue<22)
    { dealerplay = dealer_play(dealercards, numofdealercards);
    // checking what the dealer play is then adding a card if dealer hit otherwise dealer stands and final cards are printed out
        if (dealerplay == 1)
        {  
             dealercards[numofdealercards] = deck[0];
             numofdealercards++;

            num_cards--;
            for (int c = 0; c < num_cards; c++)
                {
                    deck[c] = deck[c+1];
                }
            dealerhandvalue = hand_value(dealercards, numofdealercards);
            printf("\nDealer hits(%d): ", dealerhandvalue);
            for(int i = 0; i< numofdealercards; i++)
                {
                    print_card(dealercards[i]);
                    printf("  ");
                }
            printf("\n");

        }

        else
        {   dealerhandvalue = hand_value(dealercards, numofdealercards);
            printf("Dealer stands(%d) :", dealerhandvalue);

            for(int i = 0; i< numofdealercards; i++)
                {
                    print_card(dealercards[i]);
                    printf("  ");
                }
            printf("\n");   
            break;
        }
        
    }

    // after dealer stands then checking if dealer busts
    if(dealerhandvalue>21)
        {
            *player_money += 10.0f;
            printf("\nDealer BUSTS...player wins!");
            return 1;
        }
    // after dealer stands then checking if player won
    if(playerhandvalue > dealerhandvalue)
        {
            *player_money += 10.0f;
            printf("\nPlayer wins!");
            return 1;
        }
    // after dealer stands then checking if dealer won
    if(playerhandvalue < dealerhandvalue)
        {
            printf("\nDealer wins!!!");
            return 0;
        }
    // checking for tie
    if(playerhandvalue == dealerhandvalue)
        {
            printf("\nTie!! \n");
            *player_money += 5.0f;
            return -2;
        }
    printf("\n");
}

////////////////////////////////////////////////////////////////////////////////
//
// Function     : show_player_money_histogram
// Description  : Display a histogram of the player funds by hands
//
// Inputs       : money_rounds - the list of player money by hand number
//                last_round - the hand number where the game stopped
// Outputs      : 0 always

int show_player_money_histogram( float money_rounds[], int last_round ) {


    printf("                                             Player Cash by Round \n\n");
    printf("    ---------------------------------------------------------------------------------------------------- \n");
    for( int i=200; i>=1; i = i-5)
    {
        printf("%d",i);
        // the ifs are for the spacing of the graphs y axis
        if (i<10)
            printf("   |");
        if (i<100 && i>9)
            printf("  |");
        if (i>99)
            printf(" |");
        // logic to see if player has that money in that round ( money in that round to compare with is i here)
        for( int j=0; j<100; j++)
        { 
            if (money_rounds[j]>=i)
                {
                    printf("X");
                }
            else
                {
                    printf(".");
                }
        
        }
    printf("| \n");
    }
    // x axis 
    printf("    ---------------------------------------------------------------------------------------------------- \n");
    printf("              1         2         3         4         5         6         7         8         9         10\n");
    printf("     1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890 \n");
    return 0;
}


////////////////////////////////////////////////////////////////////////////////
//
// Function     : main
// Description  : The main function for the CMPSC311 assignment #1
//
// Inputs       : argc - the number of command line parameters
//                argv - the parameters
// Outputs      : 0 if successful test, -1 if failure

int main( int argc, char **argv ) {

    /* Local variables */
    int cmp311_deck[NUM_CARDS];  // This is the deck of cards

    /* Preamble information */
    printf( "CMPSC311 - Assignment #1 - Fall 2020\n\n" );
    srand(time(NULL)) ;
    float temp = 100.0;
    float * player_money;
    player_money = &temp;
    
    /* Step #1 - create the deck of cards */

    for(int i = 0; i<52; i++)
    {
        cmp311_deck[i] = i;
    }

    /* Step #2 - print the deck of cards */

    print_cards(cmp311_deck, NUM_CARDS);
    printf("\n\n");


    /* Step #4 - shuffle the deck */

    shuffle_cards(cmp311_deck, NUM_CARDS);
    
    /* Step #5 - print the shuffled deck of cards */

     print_cards(cmp311_deck, NUM_CARDS);
     printf("\n\n");

    /* Step #6 - sort the cards */
    sort_cards(cmp311_deck, NUM_CARDS);

    /* Step #7 - print the sorted deck of cards */

    print_cards(cmp311_deck, NUM_CARDS);
    printf("\n\n");

    /* Step #9 - deal the hands */
    // playing blackjack 100 times and checking for wins, losses
    int lastround = 0;
    float moneyrounds[100]; 
    int outcome = 0;
    int playerwins=0, playerlosses=0;
    for(int x = 1; x<=100; x++)
    {   printf("---- New hand ----- \n\n");
        outcome = play_hand(cmp311_deck, NUM_CARDS, player_money);
        moneyrounds[x-1] = *player_money;
        if(outcome == 0)
            playerlosses++;
        if(outcome == 1)
            playerwins++;
        if(outcome == -1)
        {
            printf("Player does not have enough money.");
            lastround = x;
            break;
        }
        printf("\nAfter hand %d player has %.2f$ left \n", x, *player_money);
        lastround = x;
    }
    printf("------------- \n");
    printf("Blackjack done - player won %d out of 100 hands (%d.00).\n\n", playerwins, playerwins);

    /* Step 10 show historgrapm */
    // the array money rounds contains the money in every round
    show_player_money_histogram(moneyrounds,lastround);
    
    /* Exit the program successfully */
    printf( "\n\nCMPSC311 - Assignment #1 - Spring 2020 Complete.\n" );
    return( 0 );
}