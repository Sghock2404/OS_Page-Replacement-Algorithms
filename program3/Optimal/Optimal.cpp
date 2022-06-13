/*
*Optimal.cpp
*Scott Hockaday
*Course: Operating Systems CS4328
*project 3: Page Replacement Algorithms
* due: 12/02/21
*/

// Optimal (OPT)
//declared libraries
#include <iostream>
#include <list>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>
#include <deque>

const int TOTAL_PAGES = 100;
int optimal(std::deque <std::string>, int);
bool isExists(std::vector <std::string>, std::string);
bool isAppearedOnce(std::deque <std::string>&, std::string, int);

int main()
{
    int pageFrame = 30;
    std::deque<std::string>myList; //stores the randomly generated pages
    std::string generatedPage;
    int pageFaultNumber_OPT;

    //generated random page numbers
    srand((int)time(0));
    for (int i = 0; i < TOTAL_PAGES; i++)
    {
        int u;
        u = rand() % 49;
        generatedPage = std::to_string(u);
        myList.push_back(generatedPage);
        std::cout << generatedPage << " ";
    }
    //display the number of page faults
    pageFaultNumber_OPT = optimal(myList, pageFrame);
    std::cout << "\n\nNumber of page faults in Optimal: " << pageFaultNumber_OPT << std::endl;
    return 0;
}
//function to determine page faults
int optimal(std::deque<std::string> myList, int pageFrame)
{
    int pageFaults = 0;
    std::vector<std::string> pageFrameList;
    std::vector<std::string>::iterator iter;
    std::deque<std::string>::iterator iterator_One;
    int tempNum;

    while (myList.size() != 0)
    {
        if (pageFrameList.size() < pageFrame)
        {
            if (isExists(pageFrameList, myList.front()) == false)
            {
                std::string temp;
                temp = myList.front();
                pageFrameList.push_back(temp);
                myList.pop_front();
                pageFaults++;
            }
            else
            {
                myList.pop_front();
            }
        }
        else
        {
            std::string pageChange;
            if (isExists(pageFrameList, myList.front()) == true)
            {
                myList.pop_front();
            }
            else
            {
                std::string pageChange;
                tempNum = pageFrame;
                bool uselessPage = true;

                while (tempNum > 0 && uselessPage == true)
                {
                    for (iterator_One = myList.begin(); iterator_One != myList.end(); iterator_One++)
                    {
                        if (isExists(pageFrameList, *iterator_One))
                        {
                            int num = myList.size();
                            if (isAppearedOnce(myList, *iterator_One, num))
                            {

                                tempNum--;
                                pageChange = *iterator_One;
                            }
                        }
                        else
                        {
                            pageChange = *iterator_One;
                            uselessPage = false;
                            break;
                        }
                    }
                }
                //exchange the pageFrame
                for (iter = pageFrameList.begin(); iter != pageFrameList.end(); iter++)
                {
                    if (pageChange == *iter)
                    {
                        pageFrameList.insert(iter, myList.front());
                        pageFrameList.erase(iter);
                    }
                }
                myList.pop_front();
                pageFaults++;
            }
        }
    }
    pageFrameList.clear();
    return pageFaults;
}
//function to determine if page exists or not
bool isExists(std::vector <std::string> tempList, std::string iterator_One)
{
    std::vector<std::string>::iterator iter;
    for (int i = 0; i < tempList.size(); i++)
    {
        if (tempList.at(i) == iterator_One)
        {
            return true;
        }
    }
    return false;
}
//function to determine if page appears already
bool isAppearedOnce(std::deque <std::string>& tempList, std::string iterator_One, int num)
{
    int n = 0;
    for (int i = (num - 1); i < TOTAL_PAGES; i++)
    {
        if (tempList[i] == iterator_One)
        {
            n++;
        }
    }
    if (n == 1)
        return true;
    return false;
}