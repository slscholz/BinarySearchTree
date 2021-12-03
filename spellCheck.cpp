using namespace std;
#include <iostream>
#include "HashTable.h"
#include "BinarySearchTree.h"
#include <vector> 
#include <string>
#include <stdlib.h>

struct BNode{
	string word;
	int lineNum;
	bool operator < (BNode otherStruct) const{
		return ( word < otherStruct.word );
	}
};

typedef BinarySearchTree<BNode> BST;

ostream & operator << (ostream & out, BNode & temp) {
	out << temp.word << " " << temp.lineNum;
	return out;
};

void menu(string word, int lineCounter, HashTable& D, HashTable& ignored, BST& myBST);

int main(int argc, char *argv[])
{
	if(argc==1)	//catch command line input error
	{
    cerr<<"Please enter a source in your command line"<<endl;
		return 1;
	}

  //read dictionary
 	ifstream infile("dict.txt");
	string word;
  int wordCount=0;	
  vector<string> words;
  
  while(getline(infile,word))
  {
    words.push_back(word);
    wordCount++;
   // cout<< word <<endl;
    word.clear();            
  }
            
    HashTable D(wordCount+100);//hashtable accomadates 100 additions while maintaining a decent load factor
    for(int i=0; i<words.size(); i++)
    {
      D.insert(words[i]);
    }
    
    BNode notFound={"ZZZ",-1};
    BST myBST(notFound);
    
    
    char* sourceFile=argv[1];
    ifstream testFile(sourceFile);
    char letter;
    string line;    
    int lineCounter=1;
    HashTable ignored(70);
    
    while(getline(testFile,line))
    {
      for(int i=0; i<line.length();i++)
      {
        letter=line.at(i);
        letter=tolower(letter);
        while(letter!=' ') //build a word until a space is reached ignoring other symbols
        {
          if(isalpha(letter))
          {
            word=word+letter;
          }
          i++;
          if(i<line.length())
          {
            letter=line.at(i);
            letter=tolower(letter);
          }
          else
          {
            letter=' ';  //exit condition if i gets too large
          }
        }
        //try to find in hash table
        if(!D.find(word) && word.length()!=0 && !ignored.find(word))
        {
          menu(word,lineCounter, D, ignored, myBST);
          BNode bN = {word, lineCounter};
          BNode search=myBST.find(bN);
          if(search.word=="ZZZ")
          {
            myBST.insert(bN);
          }
          else if(search.word==word)//make sure to record last line
          {
            myBST.remove(bN);
            myBST.insert(bN);
          }
        }
        word.clear();
      }
       
      lineCounter++;
    }
    ofstream outfile("notfound.txt");
    myBST.printTree(outfile);

	return 0;
}

void menu(string word, int lineCounter, HashTable& D, HashTable& ignored,BST& myBST)
{
	char choice;
		cout<<"!@#$%^&*(){}   THE SPELL CHECKER PROGRAM   !@#$%^&*(){}"<<endl;
		cout<<word<<" On Line "<<lineCounter<<" Was Not Found In Dictionary"<<endl;
		cout<<"A) Add the Word To Dictionary"<<endl;
		cout<<"I) Ignore Word, and Skip Future References"<<endl;
		cout<<"G) Go On To Next Word"<<endl;
		cout<<"S) Search For A Suggested Spelling"<<endl;
		cout<<"Q) Quit Spell Checking File"<<endl;
		cout<<"Selection: ";
   
		cin>>choice;
		choice=tolower(choice);

		switch(choice)
		{
			case 'a':
			{
				D.insert(word);
				break;
			}
			case 'i':
			{
				ignored.insert(word);
				break;
			}
			case 'g':
			{
				break;
			}
			case 's':
			{
			        string temp;
			        char swap1;
	        		char swap2;
        			int i=0;
				while(i<word.length()-1)
        			{
			          temp="";
			          swap1=word.at(i);
			          swap2=word.at(i+1);
			          if(i!=0)
			          {
			            temp=word.substr(0,i);
			          }
			            temp=temp+swap2+swap1;
			          if(i<word.length()-2)
			          {
			            temp=temp+word.substr(i+2);
			          }
			          if(D.find(temp))
			          {
			            cout<<"Suggested spelling: "<<temp<<endl;
			            cout<<"Please Hit Return to Continue..."<<endl;
			            string temp2;
			            cin.ignore();
			            while(cin.get()!='\n');
			          }
       				   i++;
      			  }
				break;
			}
     			 case 'q':
    			 {
   			    	 cout<<"Now Exiting Program..."<<endl;
       				 ofstream outfile("notfound.txt");
       				 myBST.printTree(outfile);
       				 exit(3);
			 }
			default:
			{
				cerr<<"Incorrect input please try again"<<endl;
			        menu(word,lineCounter,D,ignored,myBST);
			}

		}
}
