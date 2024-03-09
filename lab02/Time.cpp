#include "Time.h"

Time::Time(int sec, int min, int hour){
    if(hour){
        hour_ = (min/60)+(sec/3600)+(hour);
        min_ = ((sec/3600)/60) + min % 60;
        sec_ = (sec%3600)%60;
    }
    else if(min){
        hour_ = 0;
        hour_ = (min/60)+(sec/3600);
        min_ = ((sec % 3600)/60) + min % 60;
        sec_ = (sec % 3600) % 60;
    }
    else if(sec){
        hour_= 0;
        min_ = 0;
        hour_ = (sec/3600);
        min_ = (sec % 3600)/60;
        sec_ = (sec % 3600) % 60;
    }
    else{
        hour_ = 0;
        min_ = 0;
        sec_ = 0;
    }
};


Time Time::operator+(const Time &other) const{
    return Time((sec_ + other.sec_) % 60,
                (sec_/60) + ((min_ + other.min_) % 60),
                (min_/60) + (hour_ + other.hour_));
};

Time Time::operator-(const Time &other) const{
    int t1 = hour_*3600 + min_*60 + sec_;
    int t2 = (other.hour_)*3600 + (other.min_)*60 + other.sec_;
    int t3 = t1 - t2;

    int t3h = t3/3600;
    t3 = t3 % 3600;
    int t3m = t3/60;
    t3 = t3 % 60;

    return Time(t3, t3m, t3h);
}

Time Time::operator*(int &C) const{
    int t1 = hour_*3600 + min_*60 + sec_;
    t1 *= C;

    int t1h = t1/3600;
    int t1m = (t1 % 3600)/60;
    t1 = (t1%3600)%60;

    return Time(t1, t1m, t1h);
}

ostream &operator<<(ostream &str, Time &rhs){
    if(rhs.hour_ == 0 && rhs.min_ == 0){
        str << rhs.sec_ << "s";
    }
    else if(rhs.hour_ == 0){
        str << rhs.min_ << "m:" << rhs.sec_ << "s";
    }
    else{
        str << rhs.hour_ << "h:" << rhs.min_ << "m:" << rhs.sec_ << "s";
    }

    return str;
};

istream &operator>>(istream &str, Time &rhs){
    str >> rhs.sec_ >> rhs.min_ >> rhs.hour_;

    rhs.hour_ += (rhs.min_/60)+(rhs.sec_/3600);
    rhs.min_ = ((rhs.sec_ % 3600)/60) + rhs.min_ % 60;
    rhs.sec_ = (rhs.sec_%3600)%60;

    return str;
}

Time::operator int(){
    return (hour_*3600)+(min_*60)+sec_;
}
