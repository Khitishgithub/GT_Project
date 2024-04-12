#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>

using namespace std;

// Node representing a book
struct BookNode
{
    string title;
    unordered_set<string> readers; // Users who have read this book
};

// Node representing a user
struct UserNode
{
    string userName;
    unordered_set<string> booksRead; // Books read by this user
};

// Graph class representing the library book recommendation system
class BookRecommendationSystem
{
private:
    unordered_map<string, BookNode> books;
    unordered_map<string, UserNode> users;

public:
    // Add a new book to the graph
    void addBook(const string &title)
    {
        if (books.find(title) == books.end())
        {
            books[title] = BookNode{title, {}};
        }
        else
        {
            cout << "Book already exists." << endl;
        }
    }

    // Add a new user to the graph
    void addUser(const string &userName)
    {
        if (users.find(userName) == users.end())
        {
            users[userName] = UserNode{userName, {}};
            cout << "User added successfully." << endl;
        }
        else
        {
            cout << "User already exists." << endl;
        }
    }

    // Record that a user has read a book
    void addRead(const string &userName, const string &title)
    {
        if (users.find(userName) != users.end() && books.find(title) != books.end())
        {
            users[userName].booksRead.insert(title);
            books[title].readers.insert(userName);
        }
        else
        {
            cout << "User or book not found." << endl;
        }
    }

    // k-nearest neighbors (kNN) algorithm to recommend books based on user similarity
    vector<string> kNNRecommendBooks(const string &userName, int k)
    {
        vector<string> recommendations;

        if (users.find(userName) == users.end())
        {
            cout << "User not found." << endl;
            return recommendations;
        }

        // Calculate Jaccard similarity between users
        unordered_map<string, double> similarityScores;
        for (const auto &user : users)
        {
            if (user.first != userName)
            {
                double commonBooks = 0;
                for (const string &book : users[userName].booksRead)
                {
                    if (user.second.booksRead.find(book) != user.second.booksRead.end())
                    {
                        commonBooks++;
                    }
                }
                double totalBooks = users[userName].booksRead.size() + user.second.booksRead.size() - commonBooks;
                similarityScores[user.first] = commonBooks / totalBooks;
            }
        }

        // Sort users based on similarity score
        vector<pair<double, string>> sortedUsers;
        for (const auto &pair : similarityScores)
        {
            sortedUsers.push_back({pair.second, pair.first});
        }
        sort(sortedUsers.begin(), sortedUsers.end(), greater<pair<double, string>>());

        // Extract top k similar users
        vector<string> similarUsers;
        for (int i = 0; i < min(k, (int)sortedUsers.size()); ++i)
        {
            similarUsers.push_back(sortedUsers[i].second);
        }

        // Recommend books read by similar users but not by the target user
        unordered_set<string> userBooks = users[userName].booksRead;
        unordered_map<string, int> bookCounts;
        for (const string &user : similarUsers)
        {
            for (const string &book : users[user].booksRead)
            {
                if (userBooks.find(book) == userBooks.end())
                {
                    bookCounts[book]++;
                }
            }
        }

        // Sort books based on count
        vector<pair<int, string>> sortedBooks;
        for (const auto &pair : bookCounts)
        {
            sortedBooks.push_back({pair.second, pair.first});
        }
        sort(sortedBooks.begin(), sortedBooks.end(), greater<pair<int, string>>());

        // Extract recommended books
        for (const auto &pair : sortedBooks)
        {
            recommendations.push_back(pair.second);
        }

        return recommendations;
    }

    // Bipartite graph algorithm to find users who repeatedly read the same books
    unordered_set<string> bipartiteAlgorithm()
    {
        unordered_set<string> repeatedReaders;
        unordered_map<string, int> bookCounts;

        // Count the number of times each book is read
        for (const auto &user : users)
        {
            for (const string &book : user.second.booksRead)
            {
                bookCounts[book]++;
            }
        }

        // Identify users who have read the same book more than once
        for (const auto &user : users)
        {
            for (const string &book : user.second.booksRead)
            {
                if (bookCounts[book] > 1)
                {
                    repeatedReaders.insert(user.first);
                    break; // Move to the next user
                }
            }
        }

        return repeatedReaders;
    }
};

int main()
{
    BookRecommendationSystem system;
 
    // Adding books
    system.addBook("Don Quixote");
    system.addBook("Alice's Adventures in Wonderland");
    system.addBook("The Adventures of Huckleberry Finn");
    system.addBook("TWuthering Heights");
    system.addBook("Jane Eyre");
    system.addBook("The Scarlet Letter");
    system.addBook("Moby Dick");
    system.addBook("The Pilgrim's Progress");
    system.addBook("A Christmas Carol");
    system.addBook("David Copperfield");
    system.addBook("A Tale of Two Cities");
    system.addBook("Little Women");
    system.addBook("Great Expectations");
    system.addBook("The Hobbit, or, There and Back Again");
    system.addBook("Frankenstein, or, the Modern Prometheus");
    system.addBook("The Great Gatsby");
    system.addBook("The Little Prince");
    system.addBook("The Call of the Wild");
    system.addBook("20,000 Leagues Under the Sea");
    system.addBook("Anna Karenina");
    system.addBook("The Wind in the Willows");
    system.addBook("The Picture of Dorian Gray");
    system.addBook("Frankenstein, or, the Modern Prometheus");
    system.addBook("The Grapes of Wrath");
    system.addBook("The House of the Seven Gables");
    system.addBook("Lord of the Flies");
    system.addBook("All Quiet on the Western Front");
    system.addBook("Gone with the Wind");
    system.addBook("The Catcher in the Rye");
    system.addBook("Fahrenheit 451");
    system.addBook("A Journey to the Center of the Earth");
    system.addBook("Vanity Fair");
    system.addBook("All Quiet on the Western Front");
    system.addBook("My Ántonia");
    system.addBook("Of Mice and Men");
    system.addBook("The Vicar of Wakefield");
    system.addBook("A Connecticut Yankee in King Arthur's Court");
    system.addBook("White Fang");
    system.addBook("Fathers and Sons");
    system.addBook("Doctor Zhivago");
    system.addBook("The Decameron");
    system.addBook("Nineteen Eighty-Four");
    system.addBook("The Jungle");
    system.addBook("Persuasion");
    system.addBook("Mansfield Park");
    system.addBook("Candide");
    system.addBook("For Whom the Bell Tolls");
    system.addBook("Far from the Madding Crowd");
    system.addBook("The Fellowship of the Ring");
    system.addBook("The Return of the Native");
    system.addBook("Sons and Lovers");
    system.addBook("Charlotte's Web");
    system.addBook("The Swiss Family Robinson");
    system.addBook("Bleak House");
    system.addBook("Père Goriot");
    system.addBook("Utopia");
    system.addBook("The History of Tom Jones, a Foundling");
    system.addBook("Harry Potter and the Prisoner of Azkaban");
    system.addBook("The Sound and the Fury");
    system.addBook("The Mill on the Floss");
    system.addBook("A Wrinkle in Time");
    system.addBook("The Hound of the Baskervilles");
    system.addBook("The Two Towers");
    system.addBook("The War of the Worlds");
    system.addBook("Middlemarch");
    system.addBook("The Age of Innocence");
    system.addBook("The Color Purple");
    system.addBook("Northanger Abbey");
    system.addBook("East of Eden");
    system.addBook("On the Road");
    system.addBook("Catch-22");
    system.addBook("Around the World in Eighty Days");
    system.addBook("Hard Times");
    system.addBook("Beloved");
    system.addBook("Mrs. Dalloway");
    system.addBook("To the Lighthouse");
    system.addBook("The Magician's Nephew");

    // Adding users
    system.addUser("Shreya Bastia");
    system.addUser("Devansh Bansal");
    system.addUser("Aditya Sahu");
    system.addUser("Goutam Kumar Nayak");
    system.addUser("Shreyash Satyananda Kar");
    system.addUser("Saroj Mohapatra");
    system.addUser("Ritesh Kumar Panda");
    system.addUser("Hardeep Mohanty");
    system.addUser("Deepak Kumar Dash");
    system.addUser("Rudra Pratap Padhi");
    system.addUser("Swastik Padhi");
    system.addUser("Chirag Agrawal");
    system.addUser("Gantyada Tejesh Kumar");
    system.addUser("Subham Kumar Sahoo");
    system.addUser("Debasish Dey");
    system.addUser("Shib Narayan Dash");
    system.addUser("Pranabesh Mishra");
    system.addUser("SSI Pritam Biswal");
    system.addUser("Swapnil Nanda");
    system.addUser("Yashika Sharma");
    system.addUser("Monali Sasamal");
    system.addUser("Rupali Pradhan");
    system.addUser("Soumya Ranjan Purohit");
    system.addUser("Pallishree Behera");
    system.addUser("Ankita Samantray");
    system.addUser("Narayan Dalei");
    system.addUser("Swastideepa Das");
    system.addUser("Pratyush Panda");
    system.addUser("Jyoti Ranjan Maharana");
    system.addUser("Nilamani Pravashchand Behera");
    system.addUser("Rahul Sethy");
    system.addUser("Deepti Sethy");
    system.addUser("Vishal Ekka");
    system.addUser("Raju Soren");
    system.addUser("Laxman Beshra");
    system.addUser("Lipika Munda");
    system.addUser("Suraj Pattnaik");
    system.addUser("Gulam Hyder");
    system.addUser("Aditya Devraj Choudhary");
    system.addUser("Harish Chandra Mohanta");
    system.addUser("Ankit Mohapatra");
    system.addUser("Prabhanjan Prabhupad Das");
    system.addUser("Jaswant Sahu");
    system.addUser("Sudipta Ranjan Sahoo");
    system.addUser("Swayam Prakash Choudhury");
    system.addUser("Kaushik Kumar Dash");
    system.addUser("Rohit Kumar Rout");
    system.addUser("Sairaj Pattnaik");
    system.addUser("Sangram Das");
    system.addUser("Mamidisetti Mohita Gangadhar");
    system.addUser("Anshuman Mishra");
    system.addUser("Jagdish Dash");
    system.addUser("Prachi Panigrahi");
    system.addUser("Sagar Sathpathy");
    system.addUser("Sagar Nayak");
    system.addUser("Anandita Dhal");
    system.addUser("Archan Swain");
    system.addUser("Aryaman Jena");
    system.addUser("Biswajeet Sahu");
    system.addUser("Anshuman Tripathy");
    system.addUser("Tashu Agrawal");
    system.addUser("Swapnita Singh");
    system.addUser("Arpita Panda");
    system.addUser("Amir Chand");
    system.addUser("Khitish Kumar Pradhan");
    system.addUser("Subhashree Biswal");
    system.addUser("Ashutosh Maharana");
    system.addUser("Abhinash Choudhury");
    system.addUser("Priyambada Acharya");
    system.addUser("Lisa Das");
    system.addUser("Arjun Murmu");
    system.addUser("Gouri Shankar Kishan");
    system.addUser("Rahul Dev Nayak");
    system.addUser("Itishree Nayak");
    system.addUser("Jitmohan Hembram");
    system.addUser("Shankar Kumar Nanda");
    system.addUser("Sushree Saswati Mishra");
    system.addUser("Bishes Martha");
    system.addUser("Pradyumna Sahu");
    system.addUser("Rajeswari Mohapatra");
    system.addUser("Ishita Pani");
    system.addUser("Chittaranjan Mohanty");
    system.addUser("Sunil Kumar Muduli");
    system.addUser("Ameli Sethy");
    system.addUser("Biswajeet Behera");
    system.addUser("Kshirodnath Mahapatra");





    // Recording books read by users
    system.addRead("Shreya Bastia", "Don Quixote");
    system.addRead("Shreya Bastia", "Alice's Adventures in Wonderland");
    system.addRead("Devansh Bansal", "Alice's Adventures in Wonderland");
    system.addRead("Devansh Bansal", "Moby Dick");
     system.addRead("Devansh Bansal", "Don Quixote");

    
    system.addRead("Aditya Sahu", "Don Quixote");
    system.addRead("Aditya Sahu", "The Adventures of Huckleberry Finn");
    system.addRead("Goutam Kumar Nayak", "Wuthering Heights");
    system.addRead("Goutam Kumar Nayak", "Jane Eyre");
    system.addRead("Goutam Kumar Nayak", "Don Quixote");
    system.addRead("Saroj Mohapatra", "Moby Dick");
    system.addRead("Saroj Mohapatra", "Don Quixote");
    system.addRead("Saroj Mohapatra", "The Scarlet Letter");
    system.addRead("Ritesh Kumar Panda", "Great Expectations");
    system.addRead("Ritesh Kumar Panda", "Don Quixote");
    system.addRead("Ritesh Kumar Panda", "Frankenstein, or, the Modern Prometheus");
    system.addRead("Ritesh Kumar Panda", "The Wind in the Willows");
    system.addRead("Hardeep Mohanty", "The Call of the Wilds");
    system.addRead("Hardeep Mohanty", "Frankenstein, or, the Modern Prometheus");
    system.addRead("Hardeep Mohanty", "The Great Gatsby");
    system.addRead("Deepak Kumar Dash", "The Great Gatsby");
    system.addRead("Deepak Kumar Dash", "Don Quixote");
    system.addRead("Rudra Pratap Padhi", "Great Expectations");
    system.addRead("Rudra Pratap Padhi", "The House of the Seven Gables");
    system.addRead("Rudra Pratap Padhi", "Jane Eyre");
    system.addRead("Swastik Padhi", "Gone with the Wind");
    system.addRead("Swastik Padhi", "Lord of the Flies");
    system.addRead("Chirag Agrawal", "Lord of the Flies");
    system.addRead("Chirag Agrawal", "All Quiet on the Western Front");
    system.addRead("Gantyada Tejesh Kumar", "The Color Purple");
    system.addRead("Gantyada Tejesh Kumar", "Gone with the Wind");
    system.addRead("Subham Kumar Sahoo", "The Swiss Family Robinson");
    system.addRead("Subham Kumar Sahoo", "The Adventures of Huckleberry Finn");
    system.addRead("Debasish Dey", "The Adventures of Huckleberry Finn");
    system.addRead("Debasish Dey", "The Magician's Nephew");
    system.addRead("Shib Narayan Dash", "The Color Purple");
    system.addRead("Shib Narayan Dash", "To the Lighthouse");
    system.addRead("Pranabesh Mishra", "East of Eden");
    system.addRead("Pranabesh Mishra", "To the Lighthouse");
    system.addRead("SSI Pritam Biswal", "The Hound of the Baskervilles");
    system.addRead("SSI Pritam Biswal", "To the Lighthouse");
    system.addRead("Swapnil Nanda", "To the Lighthouse");
    system.addRead("Swapnil Nanda", "East of Eden");
    system.addRead("Yashika Sharma", "Bleak House");
    system.addRead("Yashika Sharma", "The House of the Seven Gables");
    system.addRead("Monali Sasamal", "Hard Times");
    system.addRead("Monali Sasamal", "Don Quixote");
    system.addRead("Rupali Pradhan", "Northanger Abbey");
    system.addRead("Rupali Pradhan", "Great Expectations");
    system.addRead("Soumya Ranjan Purohit", "The Color Purple");
    system.addRead("Soumya Ranjan Purohit", "A Wrinkle in Time");
    system.addRead("Pallishree Behera", "Mrs. Dalloway");
    system.addRead("Pallishree Behera", "Alice's Adventures in Wonderland");
    system.addRead("Ankita Samantray", "Bleak House");
    system.addRead("Ankita Samantray", "Anna Karenina");
    system.addRead("Narayan Dalei", "The Sound and the Fury");
    system.addRead("Narayan Dalei", "Hard Times");
    system.addRead("Swastideepa Das", "Middlemarch");
    system.addRead("Swastideepa Das", "East of Eden");
    system.addRead("Pratyush Panda", "On the Road");
    system.addRead("Pratyush Panda", "Bleak House");
    system.addRead("Jyoti Ranjan Maharana", "The War of the Worlds");
    system.addRead("Jyoti Ranjan Maharana", "My Ántonia");
    system.addRead("Nilamani Pravashchand Behera", "The Grapes of Wrath");
    system.addRead("Nilamani Pravashchand Behera", "The Adventures of Huckleberry Finn");
    system.addRead("Rahul Sethy", "The Jungle");
    system.addRead("Rahul Sethy", "Mrs. Dalloway");
    system.addRead("Deepti Sethy", "The Pilgrim's Progress");
    system.addRead("Deepti Sethy", "A Wrinkle in Time");
    system.addRead("Vishal Ekka", "The Picture of Dorian Gray");
    system.addRead("Vishal Ekka", "Hard Times");
    system.addRead("Raju Soren", "White Fang");
    system.addRead("Raju Soren", "Anna Karenina");
    system.addRead("Laxman Beshra", "The Jungle");
    system.addRead("Laxman Beshra", "Anna Karenina");
    system.addRead("Lipika Munda", "TWuthering Heights");
    system.addRead("Lipika Munda", "Père Goriot");
    system.addRead("Suraj Pattnaik", "Anna Karenina");
    system.addRead("Suraj Pattnaik", "Fahrenheit 451");
    system.addRead("Gulam Hyder", "The Magician's Nephew");
    system.addRead("Gulam Hyder", "Anna Karenina");
    system.addRead("Aditya Devraj Choudhary", "The Adventures of Huckleberry Finn");
    system.addRead("Aditya Devraj Choudhary", "TWuthering Heightsa");
    system.addRead("Harish Chandra Mohant", "Anna Karenina");
    system.addRead("Harish Chandra Mohant", "The Jungle");
    system.addRead("Ankit Mohapatra", "The Hound of the Baskerville");
    system.addRead("Ankit Mohapatra", "Anna Karenina");
    system.addRead("Prabhanjan Prabhupad Das", "Northanger Abbey");
    system.addRead("Prabhanjan Prabhupad Das", "Fahrenheit 451");
    system.addRead("Jaswant Sahu", "20,000 Leagues Under the Sea");
    system.addRead("Jaswant Sahu", "Anna Karenina");
    system.addRead("Sudipta Ranjan Sahoo", "White Fang");
    system.addRead("Swayam Prakash Choudhury", "Beloved");
    system.addRead("Kaushik Kumar Dash", "Northanger Abbey");
    system.addRead("Kaushik Kumar Dash", "The Jungle");
    system.addRead("Rohit Kumar Rout", "The Adventures of Huckleberry Finn");
    system.addRead("Rohit Kumar Rout", "Anna Karenina");
    system.addRead("Sairaj Pattnaik", "The Hound of the Baskerville");
    system.addRead("Sairaj Pattnaik", "Beloved");
    system.addRead("Sangram Das", "Around the World in Eighty Days");
    system.addRead("Sangram Das", "The Jungle");
    system.addRead("Mamidisetti Mohita Gangadhar", "Don Quixote");
    system.addRead("Mamidisetti Mohita Gangadhar", "Anna Karenina");
    system.addRead("Anshuman Mishra", "Anna Karenina");
    system.addRead("Anshuman Mishra", "White Fang");
    system.addRead("Jagdish Dash", "The Magician's Nephew");
    system.addRead("Jagdish Dash", "To the Lighthouse");
    system.addRead("Prachi Panigrahi", "Beloved");
    system.addRead("Prachi Panigrahi", "The Adventures of Huckleberry Finn");
    system.addRead("Sagar Sathpathy", "Anna Karenina");
    system.addRead("Sagar Sathpathy", "Fahrenheit 451");
    system.addRead("Sagar Nayak", "The Magician's Nephew");
    system.addRead("Sagar Nayak", "Anna Karenina");
    system.addRead("Anandita Dhal", "TWuthering Heights");
    system.addRead("Anandita Dhal", "Anna Karenina");
    system.addRead("Archan Swain", "The Hound of the Baskerville");
    system.addRead("Archan Swain", "Anna Karenina");
    system.addRead("Aryaman Jena", "The Vicar of Wakefield");
    system.addRead("Aryaman Jena", "Don Quixote");
    system.addRead("Biswajeet Sahu", "Around the World in Eighty Days");
    system.addRead("Biswajeet Sahu", "The Adventures of Huckleberry Finn");
    system.addRead("Anshuman Tripathy", "Anna Karenina");
    system.addRead("Anshuman Tripathy", "White Fang");
    system.addRead("Tashu Agrawal", "Anna Karenina");
    system.addRead("Tashu Agrawal", "The Hound of the Baskerville");
    system.addRead("Swapnita Singh", "Anna Karenina");
    system.addRead("Swapnita Singh", "Moby Dick");
    system.addRead("Swapnita Singh","Don Quixote");
    system.addRead("Swapnita Singh", "Alice's Adventures in Wonderland");
    system.addRead("Arpita Panda", "The Adventures of Huckleberry Finn");
    system.addRead("Arpita Panda", "Around the World in Eighty Daysa");
    system.addRead("Amir Chand", "Moby Dick");
    system.addRead("Amir Chand", "Don Quixote");
    system.addRead("Amir Chand", "Alice's Adventures in Wonderland");

    system.addRead("Khitish Kumar Pradhan", "Doctor Zhivago");
    system.addRead("Khitish Kumar Pradhan", "Don Quixote");
    system.addRead("Subhashree Biswal", "Don Quixote");
    system.addRead("Subhashree Biswal", "Anna Karenina");
    system.addRead("Ashutosh Maharana", "The Vicar of Wakefield");
    system.addRead("Ashutosh Maharana", "Anna Karenina");
    system.addRead("Abhinash Choudhury", "TWuthering Heights");
    system.addRead("Abhinash Choudhury", "Anna Karenina");
    system.addRead("Priyambada Acharya", "Doctor Zhivago");
    system.addRead("Priyambada Acharya", "Anna Karenina");
    system.addRead("Lisa Das", "Anna Karenina");
    system.addRead("Lisa Das", "The Hound of the Baskerville");
    system.addRead("Arjun Murmu", "The Vicar of Wakefield");
    system.addRead("Arjun Murmu", "Anna Karenina");
    system.addRead("Gouri Shankar Kishan", "Fahrenheit 451");
    system.addRead("Gouri Shankar Kishan", "20,000 Leagues Under the Sea");
    system.addRead("Rahul Dev Nayak", "Anna Karenina");
    system.addRead("Rahul Dev Nayak", "Doctor Zhivago");
    system.addRead("Itishree Nayak", "Fahrenheit 451");
    system.addRead("Itishree Nayak", "Around the World in Eighty Days");
    system.addRead("Jitmohan Hembram", "The Hound of the Baskerville");
    system.addRead("Jitmohan Hembram", "Anna Karenina");
    system.addRead("Shankar Kumar Nanda", "White Fang");
    system.addRead("Shankar Kumar Nanda", "20,000 Leagues Under the Sea");

    // Using k-nearest neighbors algorithm to recommend books
    string userName;
    cout << "Enter your username: ";
    getline(cin, userName);

    // Using k-nearest neighbors algorithm to recommend books
    vector<string> kNNRecommendations = system.kNNRecommendBooks(userName, 2);
    cout << "Recommendations using kNN algorithm:" << endl;
    for (const auto &book : kNNRecommendations)
    {
        cout << book << endl;
    }
    cout << endl;

    // Using bipartite graph algorithm to find users who repeatedly read the same books
    unordered_set<string> repeatedReaders = system.bipartiteAlgorithm();
    // cout << "Users who read the same book repeatedly:" << endl;
    // for (const auto &user : repeatedReaders)
    // {
    //     cout << user << endl;
    // }

    return 0;
}
