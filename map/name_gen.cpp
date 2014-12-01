
#include <stdlib.h>
#include "name_gen.h"

#define LAST_LETTER_CANDIDATES_MAX  5

void CWeightedLetterNamegen::init(){

    m_sizes.clear();
    //m_letters.clear();
    m_firstLetterSamples.clear();
    m_lastLetterSamples.clear();

    for (unsigned int i=0; i < m_names.size(); i++){

        std::string name=m_names[i];
        // (1) Insert size
        m_sizes.push_back(name.size());
        // (2) Grab first letter
        m_firstLetterSamples.push_back(std::string(1,name[0]));
        // (3) Grab last letter
        m_lastLetterSamples.push_back(std::string( 1, name[name.size()-1] ));
        // (4) Process all letters
        for(unsigned int i=0; i < name.size()-1; i++){
            std::string letter = std::string(1, name[i] );
            std::string nextLetter = std::string(1,  name[i + 1] );

            if (!m_letters.count(letter)){
                m_letters[letter] = new CWeightedLetter(letter);
            }

            m_letters[letter]->addNextLetter(nextLetter);
        }
    }

    for(auto it = m_letters.begin(); it != m_letters.end(); ++it){
        it->second->nextLetters->expandSamples();
    }

    m_initialized = true;

}

std::vector<std::string> CWeightedLetterNamegen::generate(unsigned int amountToGenerate){
    // Initialize if called for the first time
    if (!m_initialized) init();

    std::vector<std::string> result;

    for(unsigned int nameCount = 0; nameCount < amountToGenerate;){
        std::string name="";
    // Pick size
        int size = m_sizes[ rand() % m_sizes.size() ];
    // Pick first letter
        std::string firstLetter = m_firstLetterSamples[ rand() % m_firstLetterSamples.size() ];

        name+=firstLetter;


        for (int i = 1; i < size-2; i++)
        {
            // Only continue if the last letter added was non-null
            if (name[i - 1])
            {
                name+=this->getRandomNextLetter( std::string(1,name[i - 1]) );
            }
            else
            {
                break;
            }
        }

        // Attempt to find a last letter
        for(int lastLetterFits = 0; lastLetterFits < LAST_LETTER_CANDIDATES_MAX; lastLetterFits++){

            std::string lastLetter=m_lastLetterSamples[ rand() % m_lastLetterSamples.size() ];
            std::string intermediateLetterCandidate=this->getIntermediateLetter( std::string(1,name[name.size() - 1]), lastLetter);
            // Only attach last letter if the candidate is valid (if no candidate, the antepenultimate letter always occurs at the end)

            if (intermediateLetterCandidate!=""){

                name+=intermediateLetterCandidate;
                name+=lastLetter;
                break;

            }

        }

        // Check that the word has no triple letter sequences, and that the Levenshtein distance is kosher
        if (this->tripleLetterCheck(name) && this->checkLevenshtein(name))
        {
            result.push_back(name);
            // Only increase the counter if we've successfully added a name
            nameCount++;
        }

    }

    return result;
}


std::string CWeightedLetterNamegen::getRandomNextLetter(std::string letter){
    std::string result="";
    if(m_letters.count(letter)){

        std::vector<std::string> letters=m_letters[letter]->nextLetters->letterSamples;
        result = letters[ rand() % letters.size() ];
    }

    return result;
}

std::string CWeightedLetterNamegen::getIntermediateLetter(std::string letterBefore, std::string letterAfter){

    if(letterBefore!="" && letterAfter!="" && m_letters.count(letterBefore)){
        // First grab all letters that come after the 'letterBefore'

        std::map<std::string,CWeightedLetterCounter*> letterCandidates;
        letterCandidates=m_letters[letterBefore]->nextLetters->letters;

        std::string bestFitLetter = "";
        unsigned int bestFitScore = 0;

        // Step through candidates, and return best scoring letter
        for(auto it=letterCandidates.begin(); it != letterCandidates.end(); ++it){
            if(m_letters.count(it->second->letter)){
                CWeightedLetter *letterInNextLetters=m_letters[it->second->letter];
                CWeightedLetterGroup *weightedLetterGroup = letterInNextLetters->nextLetters;
                if(weightedLetterGroup->letters.count(letterAfter)){
                    CWeightedLetterCounter *letterCounter = weightedLetterGroup->letters[letterAfter];
                    if(letterCounter->count > bestFitScore){
                         bestFitLetter = it->second->letter;
                         bestFitScore = letterCounter->count;
                    }
                }
            }
        }
        return bestFitLetter;
    }
    else{
        // If any of the passed parameters were null, return null. This happens when the letterBefore has no candidates.
        return "";
    }

}

bool CWeightedLetterNamegen::tripleLetterCheck(std::string name){
    return true;
}

bool CWeightedLetterNamegen::checkLevenshtein(std::string name){
    return true;
}

std::string CWeightedLetterNamegen::toCyrilic(std::string name){
    std::string result;
    for(unsigned int i=0; i < name.size(); i++){
        std::string c="";
        switch(name[i]){

            case 'a': c="а"; break;
            case 'b': c="б"; break;
            case 'c': c="ц"; break;
            case 'd': c="д"; break;
            case 'e': c="е"; break;
            case 'f': c="ф"; break;
            case 'g': c="г"; break;
            case 'h': c="х"; break;
            case 'i': c="и"; break;
            case 'j': c="ж"; break;
            case 'k': c="к"; break;
            case 'l': c="л"; break;
            case 'm': c="м"; break;
            case 'n': c="н"; break;
            case 'o': c="о"; break;
            case 'p': c="п"; break;
            case 'q': c="кю"; break;
            case 'r': c="р"; break;
            case 's': c="с"; break;
            case 't': c="т"; break;
            case 'u': c="у"; break;
            case 'v': c="в"; break;
            case 'w': c="в"; break;
            case 'x': c="кс"; break;
            case 'y': c="й"; break;
            case 'z': c="з"; break;

            case 'A': c="А"; break;
            case 'B': c="Б"; break;
            case 'C': c="Ц"; break;
            case 'D': c="Д"; break;
            case 'E': c="Е"; break;
            case 'F': c="Ф"; break;
            case 'G': c="Г"; break;
            case 'H': c="Х"; break;
            case 'I': c="И"; break;
            case 'J': c="Ж"; break;
            case 'K': c="К"; break;
            case 'L': c="Л"; break;
            case 'M': c="М"; break;
            case 'N': c="Н"; break;
            case 'O': c="О"; break;
            case 'P': c="П"; break;
            case 'Q': c="Кю"; break;
            case 'R': c="Р"; break;
            case 'S': c="С"; break;
            case 'T': c="Т"; break;
            case 'U': c="У"; break;
            case 'V': c="В"; break;
            case 'W': c="В"; break;
            case 'X': c="Кс"; break;
            case 'Y': c="Й"; break;
            case 'Z': c="З"; break;
            default: break;
        }
        result+=c;
    }
    return result;
}
