//Connor Marshall
//Data Structures and Algorithms
//Project 1 "Comparing Sort Algorithms"
//1-18-22

#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <ctime>
#include <cstdlib>

using namespace std;

//smart runtime bubble sort function performs sort on passed in stl list
void bubbleS(list<string> &inList)
{
  //store front and back of list
  list<string>::iterator start = inList.begin();
  list<string>::iterator end = inList.end();

  int swaps = 1;
  while(swaps > 0)
  {
    swaps = 0;

    //two iterators that remain 1 apart
    list<string>::iterator it = start;
    list<string>::iterator rightOfIt = it;

    if(inList.size() > 1) rightOfIt++;

    for(it; rightOfIt!= end; ++it)
    {
      if(*it > *rightOfIt)
      {
        string store = *it;
        it->assign(*rightOfIt);
        rightOfIt->assign(store);
        swaps++;
      }
      rightOfIt++;
    }
  }
}

//call system sort on inputted list
void sysS(list<string> &inList)
{
  inList.sort();
}

//child function for merge sort. Combines 2 in order lists in order
list<string> merge(list<string> listA, list<string> listB)
{
  list<string> returnList;
  //while both lists have elements add the smallest element to the new list
  while(!listA.empty() && !listB.empty())
  {
    if(listA.front() < listB.front())
    {
      returnList.push_back(listA.front());
      listA.pop_front();
    }
    else
    {
      returnList.push_back(listB.front());
      listB.pop_front();
    }
  }

  //while list A is not empty add the elements to the new list front to back
  while(!listA.empty())
  {
    returnList.push_back(listA.front());
    listA.pop_front();
  }

  //if A was already empty then B would run in it's place
  while(!listB.empty())
  {
    returnList.push_back(listB.front());
    listB.pop_front();
  }

  return returnList;
}

//list implementation of merge sort
void mergeS(list<string> &inList)
{
  //base case
  if(inList.size() <= 1)
    return;

  //split the list into 2 lists
  list<string> frontHalf;
  list<string> backHalf;
  int listPos;
  for(string item: inList)
  {
    if(listPos < inList.size()/2)
      frontHalf.push_back(item);
    else
      backHalf.push_back(item);

    listPos++;
  }
  
  //recursivly call mergeS on each list
  mergeS(frontHalf);
  mergeS(backHalf);

  inList = merge(frontHalf,backHalf);
}

//list implementation of quick sort
void quickS(list<string> &inList)
{
  //base case
  if(inList.size() <= 1)
    return;

  //determine random item from the list
  int randI = rand() % inList.size();
  string pivot;
  int itemID = 0;
  for(string item: inList)
  {
    if(itemID == randI)
    {
      pivot = item;
      break;
    } 
    itemID++;
  }

  list<string> lessThan;
  list<string> equalTo;
  list<string> greaterThan;

  //groups all elements from inList to three groups
  while(!inList.empty())
  {
    string front = inList.front();

    if(front < pivot)
    {
      lessThan.push_back(front);
    }
    else if(front == pivot)
    {
      equalTo.push_back(front);
    }
    else
    {
      greaterThan.push_back(front);
    }

    inList.pop_front();
  }
  quickS(lessThan);
  quickS(greaterThan);

  //recombine the now ordered lists into original list
  for(string item: lessThan)
  {
    inList.push_back(item);
  }
  for(string item: equalTo)
  {
    inList.push_back(item);
  }
  for(string item: greaterThan)
  {
    inList.push_back(item);
  }

}

//check and fix new insert into a heap
void upHeap(string inHeap[], int insertionPoint)
{
  bool swapped = true;
  int currN = insertionPoint;
  while(swapped)
  {
    //if at the root
    if(currN == 1)
    {
      swapped = false;
    }
    //if the parent is greater than the new child
    else if(inHeap[currN]<inHeap[currN/2])
    {
      string store = inHeap[currN];
      inHeap[currN] = inHeap[currN/2];
      inHeap[currN/2] = store;
      currN /= 2;
    }
    else swapped = false;
  }
}

void downHeap(string * inHeap, int maxNode)
{
  //if the heap only has 1 node
  if(maxNode <= 1)
  {
    inHeap[1] = "";
    return;
  }

  //swap max node with root
  inHeap[1] = inHeap[maxNode];
  inHeap[maxNode] = "";
  maxNode--;

  bool swapped = true;
  int currN = 1;
  while(swapped)
  {
    //if both childs are empty
    if(currN*2 > maxNode) 
      swapped = false;

    //if the right child is empty
    else if(currN*2+1 > maxNode)
    {
      if(inHeap[currN] > inHeap[currN*2])
      {
        string store = inHeap[currN];
        inHeap[currN] = inHeap[currN*2];
        inHeap[currN*2] = store;

        currN *= 2;
      }
      else swapped = false;
    }

    //if both childs are full
    else
    {
      //if can swap with niether children
      if(inHeap[currN] < inHeap[currN*2] && inHeap[currN] < inHeap[currN*2+1])
        swapped = false;

      //if can swap with both children
      else if(inHeap[currN] > inHeap[currN*2] && inHeap[currN] > inHeap[currN*2+1])
      {
        if(inHeap[currN*2]<inHeap[currN*2+1])
        {
          string store = inHeap[currN];
          inHeap[currN] = inHeap[currN*2];
          inHeap[currN*2] = store;

          currN *= 2;
        }
        else
        {
          string store = inHeap[currN];
          inHeap[currN] = inHeap[currN*2+1];
          inHeap[currN*2+1] = store;

          currN = currN*2 +1;
        }
      }
      //if can swap with left
      else if(inHeap[currN] > inHeap[currN*2])
      {
        string store = inHeap[currN];
        inHeap[currN] = inHeap[currN*2];
        inHeap[currN*2] = store;

        currN *= 2;
      }
      //if can swap with right
      else
      {
        string store = inHeap[currN];
        inHeap[currN] = inHeap[currN*2+1];
        inHeap[currN*2+1] = store;

        currN = currN*2 +1;
      }


    }
  }
}

//implement data into a heap and pull off to sort
void heapS(list<string> &inList)
{
  //creating and inserting into a heap
  string myHeap[inList.size()+1]; 
  int insertionPoint = 1;

  for(string item: inList)
  {
    myHeap[insertionPoint] = item;
    upHeap(myHeap, insertionPoint);
    insertionPoint++;
  }

  inList.clear();

  //pulling from heap and readding to list
  int maxNode = insertionPoint -1;
  while(maxNode >= 1)
  {
  inList.push_back(myHeap[1]);
  downHeap(myHeap, maxNode);
  maxNode--;
  }
}


int main(int argc, char *argv[])
{
  //sets rand seed
  srand((unsigned int)time(NULL));

  //read in command line arguments
  string fileName = argv[1];
  string sortMethod = argv[2];

  bool printResults = false;

  if(argc > 3)
    if(string(argv[3]) == "-print") 
      printResults = true;

  //create and open file streams
  ifstream inputFile;
  inputFile.open(fileName);

  //read and store from file
  int numVals;
  inputFile >> numVals;

  list<string> myList;
  string currLine;
  for(int i=0; i < numVals; i++)
  {
    inputFile >> currLine;
    myList.push_back(currLine);  
  }
  
  //close inputFile
  inputFile.close();

  //perform inputted sort method
  if(sortMethod == "bubble")
  {
    bubbleS(myList);
  }
  else if(sortMethod == "sys")
  {
    sysS(myList);
  }
  else if(sortMethod == "merge")
  {
    mergeS(myList);
  }
  else if(sortMethod == "quick")
  {
    quickS(myList);
  }
  else if(sortMethod == "heap")
  {
    heapS(myList);
  }


  //prints to stdout if specified in command line
  if(printResults)
  {
    for(string item: myList)
    {
      cout << item << endl;
    }
  }

    return 0;
}
