#include "cards.h"

QString card::suit_str[] = {"clubs", "diamonds", "hearts", "spades"};

QString card::rank_to_string ( int myRank)
{
    QString out;
    switch(myRank)
    {
    case 1:
        out = "ace";
        break;
    case 2:
        out = "two";
        break;
    case 3:
        out = "three";
        break;
    case 4:
        out = "four";
        break;
    case 5:
        out = "five";
        break;
    case 6:
        out = "six";
        break;
    case 7:
        out = "seven";
        break;
    case 8:
        out = "eight";
        break;
    case 9:
        out = "nine";
        break;
    case 10:
        out = "ten";
        break;
    case 11:
        out = "jack";
        break;
    case 12:
        out = "queen";
        break;
    case 13:
        out = "king";
        break;
    }
    return out;
}

int card::suit_to_enum ( QString mySuit )
{
    suits_t out = clubs;
    if(mySuit == "clubs")
    {
        out = clubs;
    }
    else if(mySuit == "diamonds")
    {
        out = diamonds;
    }
    else if(mySuit == "hearts")
    {
        out = hearts;
    }
    else if(mySuit == "spades")
    {
        out = spades;
    }

    return out;
}
