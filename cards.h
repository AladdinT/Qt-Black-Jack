#ifndef CARDS_H
#define CARDS_H
#include <QString>

class card
{
private:
    enum suits_t { clubs=0, diamonds=13, hearts=26, spades=39 };

    int rank;
    QString suit;
    QString rank_str;
    QString full_name;
    int id;

protected:
    static QString rank_to_string ( int myRank);
    static int suit_to_enum ( QString mySuit );

public:
    static QString suit_str[4];
    void init_card(int myRank, QString mySuit)
    {
        rank = myRank;
        suit = mySuit;
        full_name = rank_to_string(myRank) + "-of-" + suit;
        id = ( suit_to_enum(mySuit) ) + rank;
    }
    QString whoami()
    {
        return full_name;
    }
    QString getName()
    {
        return rank_to_string(rank);
    }

    QString getSuit()
    {
        return suit;
    }
    int getRank()
    {
        return rank;
    }


};
#endif // CARDS_H
