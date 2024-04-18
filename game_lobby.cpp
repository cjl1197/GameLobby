//Game Lobby
//Simulates a game lobby where players wait

#include <iostream>
#include <string>

using namespace std;

class Player
{
public:  
    Player(const string& name = "");
    string GetName() const;
    Player* GetNext() const;
    void SetNext(Player* next);
    
private:
    string m_Name;
    Player* m_pNext;  //Pointer to next player in list
};

Player::Player(const string& name): 
    m_Name(name), 
    m_pNext(0) 
{}

string Player::GetName() const
{
    return m_Name;
}

Player* Player::GetNext() const
{
    return m_pNext;
}

void Player::SetNext(Player* next)
{
    m_pNext = next;
}

class Lobby
{
    friend ostream& operator<<(ostream& os, const Lobby& aLobby);
    
public:
    Lobby();
    ~Lobby();
    void AddPlayer();
    void DeletePlayer();
    void SearchPlayer();
    void Clear();
    
private:
    Player* m_pHead;  
};

Lobby::Lobby():
    m_pHead(0)
{}

Lobby::~Lobby()
{
    Clear();
}

void Lobby::AddPlayer()
{
    //create a new player node
    cout << "Please enter the name of the new player: ";
    string name;
    
    cin >> name;
    
    Player* pNewPlayer = new Player(name);

    //if list is empty, make head of list this new player
    if (m_pHead == 0)
    {
        m_pHead = pNewPlayer;
    }
    //otherwise find the end of the list and add the player there
    else
    {
        if (name < m_pHead->GetName())
        {
            Player* pTemp = m_pHead;
            m_pHead = pNewPlayer;
            m_pHead->SetNext(pTemp);
        }
        
        else
        {
            Player* pIter = m_pHead;

            while (pIter != 0)
            {
                if (name > pIter->GetName() && pIter->GetNext() == 0)
                    //pIter->SetNext(pNewPlayer);
                    break;
                else if (name > pIter->GetName() && name < pIter->GetNext()->GetName())
                    break;

                else
                    pIter = pIter->GetNext();
       

            }
            if (name > pIter->GetName() && pIter->GetNext() == 0)
                pIter->SetNext(pNewPlayer);

            else
            {
                Player* pTemp = pIter->GetNext();
                pIter->SetNext(pNewPlayer);
                pIter->SetNext(pTemp);
            }
        }
    }
}

void Lobby::DeletePlayer()
{
    string playerName; // player name to delete
    bool found = false;
   
    Player* pItter = m_pHead;
    Player* pItter2 = m_pHead;

    cout << "Enter player name to delete: ";
    cin >> playerName;
    while (pItter != 0)
    {
        if (playerName == m_pHead->GetName())
        {
            Player* pTemp = m_pHead;
            m_pHead = m_pHead->GetNext();
            delete pTemp;
            pItter = m_pHead;
            cout << "Player Deleted!\n";
            found = true;
        }
        else
            pItter = pItter->GetNext();
    }

    pItter = m_pHead;
    pItter2 = m_pHead;

    while (pItter != 0)
    {

        
        if (pItter->GetName() == playerName)
        {
            found = true;
            while (pItter2->GetNext() != pItter)
            {
                pItter2 = pItter2->GetNext();
            }

            pItter2->SetNext(pItter->GetNext());
            delete pItter;
            pItter = pItter2;
            cout << "Player Deleted!\n"; 
        }
            pItter = pItter->GetNext();
    }
    if (!found)
        cout << "Player Not Found!\n";

}

void Lobby::SearchPlayer()
{
    string name = "";
    bool found = false;

    if (m_pHead == 0)
    {
        cout << "\n Player Lobby is empty.";
    }
    else
    {
        Player* pItter1 = m_pHead;
        int position = 0;

        cout << "Enter name to search: ";
        cin >> name;
        cout << name << endl;

        while (pItter1 != 0)
        {
            ++position;

            if (pItter1->GetName() == name)
            {
                cout << name << " was found!  " << name << " was at position " << position << ".\n";
                found = true;
            }
            pItter1 = pItter1->GetNext();
        }
    }
    if (!found)
        cout << "Player was not found!\n";
}

void Lobby::Clear()
{
    while (m_pHead != 0)
    {
        if (m_pHead == 0)
        {
            cout << "The game lobby is empty.  No one to remove!\n";
        }
        else
        {
            Player* pTemp = m_pHead;
            m_pHead = m_pHead->GetNext();
            delete pTemp;
        };
    }
}

ostream& operator<<(ostream& os, const Lobby& aLobby)
{
    Player* pIter = aLobby.m_pHead;

    os << "\nHere's who's in the game lobby:\n";
    if (pIter == 0)
    {
        os << "The lobby is empty.\n";
    }
    else
    {
        while (pIter != 0)
        {   
            os << pIter->GetName() << endl;
	        pIter = pIter->GetNext();
        }
    }

    return os;
}

int main()
{
    Lobby myLobby;
    int choice;

    
    do
	{
	    cout << myLobby;
        cout << "\nGAME LOBBY\n";
        cout << "0 - Exit the program.\n";
        cout << "1 - Add a player to the lobby.\n";
        cout << "2 - Search for a player.\n";
        cout << "3 - Delete specific player from the lobby.\n";
        cout << "4 - Clear the lobby.\n";
        cout << endl << "Enter choice: ";
        cin >> choice;
        
        

        switch (choice)
        {
            case 0: cout << "Good-bye.\n"; break;
	        case 1: myLobby.AddPlayer(); break; 
            case 2: myLobby.SearchPlayer(); break;
            case 3: myLobby.DeletePlayer(); break;
            case 4: myLobby.Clear(); break;
            default: cout << "That was not a valid choice.\n";
        }
	}
    while (choice != 0);
    
    return 0;
}
