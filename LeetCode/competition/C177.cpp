//
// Created by Administrator on 2020/2/23 0023.
//

#include <iostream>
#include <cstring>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:

    bool IsLeap(int year)
    {
        return (year % 4 ==0 || year % 400 ==0) && (year % 100 !=0);
    }

//上面的StringToDate函数用于取出日期中的年月日并判断日期是否合法
//从字符中最得年月日 规定日期的格式是yyyy-mm-dd
    bool StringToDate(string date, int& year, int& month, int& day)
    {
        year = atoi((date.substr(0,4)).c_str());
        month = atoi((date.substr(5,2)).c_str());
        day = atoi((date.substr(8,2)).c_str());
        int DAY[12]={31,28,31,30,31,30,31,31,30,31,30,31};
        if(IsLeap(year)){
            DAY[1] = 29;
        }
        return year >= 0 && month<=12 && month>0 && day<=DAY[month] && day>0;
    }

//DayInYear能根据给定的日期，求出它在该年的第几天，代码如下
    int DayInYear(int year, int month, int day)
    {
        //int _day = 0;
        int DAY[12]={31,28,31,30,31,30,31,31,30,31,30,31};
        if(IsLeap(year))
            DAY[1] = 29;
        for(int i=0; i<month - 1; ++i)
        {
            day += DAY[i];
        }
        return day;
    }

    int daysBetweenDates(string date1, string date2)
    {
        //取出日期中的年月日
        int year1, month1, day1;
        int year2, month2, day2;
        if(!StringToDate(date1, year1, month1, day1) || !StringToDate(date2, year2,month2,day2))
        {
            cout<<"输入的日期格式不正确";
            return -1;
        }
        if(year1 == year2 && month1 == month2)
        {
            return day1 > day2 ? day1 - day2 : day2 - day1;

            //如果年相同
        }else if(year1 == year2)
        {
            int d1, d2;
            d1 = DayInYear(year1, month1, day1);
            d2 = DayInYear(year2, month2, day2);
            return d1 > d2 ? d1 - d2 : d2 - d1;

            //年月都不相同
        }else{
            //确保year1年份比year2早
            if(year1 > year2)
            {
                //swap进行两个值的交换
                swap(year1, year2);
                swap(month1, month2);
                swap(day1, day2);
            }
            int d1,d2,d3;
            if(IsLeap(year1))
                d1 = 366 - DayInYear(year1,month1, day1); //取得这个日期在该年还于下多少天
            else
                d1 = 365 - DayInYear(year1,month1, day1);
            d2 = DayInYear(year2,month2,day2); //取得在当年中的第几天
            cout<<"d1:"<<d1<<", d2:"<<d2;

            d3 = 0;
            for(int year = year1 + 1; year < year2; year++)
            {
                if(IsLeap(year))
                    d3 += 366;
                else
                    d3 += 365;
            }
            return d1 + d2 + d3;
        }
    }
//日期格式为yyyy-mm-dd
//求两个日期之间的相隔天数
    int daysBetweenDates(string date1, string date2) {
        const char *bgDate = date1.c_str();
        const char *exDate = date2.c_str();
        if (bgDate == NULL || exDate == NULL)
            return 0;
        int by, bm, bd, ey, em, ed;
        int days = 0;
        if (strcmp(bgDate, exDate) > 0) {
            sscanf(exDate, "%d-%d-%d", &by, &bm, &bd);
            sscanf(bgDate, "%d-%d-%d", &ey, &em, &ed);
        } else{
            sscanf(bgDate, "%d-%d-%d", &by, &bm, &bd);
            sscanf(exDate, "%d-%d-%d", &ey, &em, &ed);
        }


        if (ey - by >= 1) {
            days += ((ey - (by + 1)) / 4) * (365 * 3 + 366);
            int tmp = (ey - (by + 1)) % 4;
            for (int i = 1; i <= tmp; ++i) {
                if (IsLeapYear(by + 1))
                    days += 366;
                else
                    days += 365;
            }
            days += (GetRemainDays(by, bm, bd) + GetNowDays(ey, em, ed));
        } else {
            days += (GetNowDays(ey, em, ed) - GetNowDays(by, bm, bd));
        }
        return days;
    }

    bool validateBinaryTreeNodes(int n, vector<int> &leftChild, vector<int> &rightChild) {
        int max = -1;
        unordered_set<int> set;
        for (int &i:leftChild) {
            if(i>max){
                max = i;
            } else if (i!=-1&&i<max){
                return false;
            }
            if(i!=-1){
                if(set.find(i)!=set.end()){
                    return false;
                } else{
                    set.insert(i);
                }
            }
        }
        max = -1;
        for (int &i:rightChild) {
            if(i>max){
                max = i;
            } else if (i!=-1&&i<max){
                return false;
            }
            if(i!=-1){
                if(set.find(i)!=set.end()){
                    return false;
                } else{
                    set.insert(i);
                }
            }
        }
        return set.size() == n;
    }

    vector<int> closestDivisors(int num) {

    }
};