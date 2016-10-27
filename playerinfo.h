#ifndef PLAYERINFO_H
#define PLAYERINFO_H


class PlayerInfo
{
public:
    PlayerInfo();
    virtual ~PlayerInfo();
    unsigned int getCash() { return cash_; }
    void setCash_(unsigned int val) { cash_ = val; }
    unsigned int getScore() { return score_; }
    void setScore_(unsigned int val) { score_ = val; }
protected:
// private:
    unsigned int cash_;
    unsigned int score_;
};



#endif // PLAYERINFO_H
