#include <bits/stdc++.h>
#include <tuple>
#include <cstdlib>

using namespace std;

class TrieNode
{
public:
    unordered_map<char, TrieNode *> hashmap;
    std::string s;
    std::string alphabet = "$abcdefghijklmnopqrstuvwxyz";
    string prevstring = "";
    string stringBuilder = "";
    vector<string> words;

    // function to create the suffix trie
    bool insert(TrieNode *&root, string suffix)
    {
        TrieNode *curr = root;
        char letter;
        for (int i = 0; i < suffix.size(); i++)
        {
            letter = suffix[i];
            if (curr->hashmap.find(letter) == curr->hashmap.end())
            {
                curr->hashmap[letter] = new TrieNode;
            }
            curr = curr->hashmap[letter];
        }
        return 1;
    }

    // function to search for a word or sentence
    tuple<bool, TrieNode *> search(TrieNode *root, string s)
    {
        TrieNode *curr = root;
        for (int i = 0; i < s.size(); i++)
        {
            if (curr->hashmap.find(s[i]) == curr->hashmap.end())
            {
                return {0, root};
            }
            curr = curr->hashmap[s[i]];
        }
        return {1, curr};
    }

    // recursive depth first search
    void dfs(TrieNode *root, std::vector <string> & suggestions, int level, string original)
    {
        
        TrieNode *curr;
        for (int i = 0; i < alphabet.size(); i++)
        {
            if (root->hashmap.find(alphabet[i]) == root->hashmap.end())
            {
            }
            else
            {
                if (alphabet[i] == '$')
                {
                    string buildFinal;
                    int checkIfSubstring = level - stringBuilder.length();
                    if (checkIfSubstring > 0)
                    {
                        prevstring = prevstring.substr(0, checkIfSubstring) + stringBuilder;
                        buildFinal = original + prevstring;
                    }
                    else
                    {
                        prevstring = stringBuilder;
                        buildFinal = original + prevstring;
                    }
                    stringBuilder = "";
                    suggestions.push_back(buildFinal);
                }
                else
                {
                    stringBuilder += alphabet[i];
                }

                TrieNode *curr;
                curr = root->hashmap[alphabet[i]];
                dfs(curr, suggestions, level + 1, original);
            }
        }
        
    }

    // initializer of depth first search
    vector<string> preorder(TrieNode *root, string originalString)
    {
        int level = 0;
        int prev_level = 0;
        std::string prev;
        std::vector<string> suggestions;
        dfs(root, suggestions, level, originalString);
        return suggestions;
    }
};
