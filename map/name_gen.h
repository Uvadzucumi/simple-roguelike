#ifndef NAME_GEN_H_INCLUDED
#define NAME_GEN_H_INCLUDED

#include <string>
#include <vector>
#include <map>

struct CWeightedLetterCounter{
    public:
        std::string letter;
        unsigned int count;

        CWeightedLetterCounter(std::string p_letter){
            letter = p_letter;
            count=0;
        }
};


class CWeightedLetterGroup{
    public:
        std::map<std::string,CWeightedLetterCounter*> letters;
        std::vector<std::string> letterSamples;


    void add(std::string letter){

        if (!letters.count(letter))
        {
            letters[letter] = new CWeightedLetterCounter(letter);
        }

        letters[letter]->count++;
    }

    void expandSamples(){
        letterSamples.clear();
        for(auto it = letters.begin(); it != letters.end(); ++it){
            for(unsigned int i=0; i < it->second->count; i++)
            {
                letterSamples.push_back(it->second->letter);
            }
        }
    }

};

class CWeightedLetter{
    public:
        std::string letter;
		CWeightedLetterGroup *nextLetters;

        CWeightedLetter(std::string p_letter){
            nextLetters = new CWeightedLetterGroup();
            letter=p_letter;
		}

		void addNextLetter(std::string nextLetter){
			nextLetters->add(nextLetter);
		}
};

class CWeightedLetterNamegen{

        bool m_initialized;

        std::vector<std::string> m_names;
        std::vector<int> m_sizes;
        std::map<std::string,CWeightedLetter*> m_letters;
        std::vector<std::string> m_firstLetterSamples;
        std::vector<std::string> m_lastLetterSamples;

    public:
        CWeightedLetterNamegen(std::vector<std::string> names){
            m_initialized=false;
            m_names=names;
        }

        CWeightedLetterNamegen(){
            std::vector<std::string> names={
                "Afrin",
                "Vaiarda",
                "Antrea",
                "Villerim",
                "Elltein",
                "Ullared",
                "Niana",
                "Argus",
                "Katmur",
                "Lanned",
                "Leskaron",
                "Laon",
                "Lavor",
                "Lan",
                "Navenn",
                "Ismar",
                "Famar",
                "Fluran",
                "Arhmen",
                "Torion",
                "Damir",
                "Abbas",
                "Monkut",
                "Tuan",
                "Abidan",
                "Aielet",
                "Ananta",
                "Aiman",
                "Askadiya",
                "Irsay",
                "Madok",
                "Ruzal",
                "Sagadat",
                "Simha",
                "Sagdanur",
                "Ardashir",
                "Anzgar",
                "Niborn",
                "Munkus"
            };
            m_initialized=false;
            m_names=names;
        }

        void init();

        std::vector<std::string> generate(unsigned int amountToGenerate = 1);

        std::string getRandomNextLetter(std::string letter);
        std::string getIntermediateLetter(std::string letterBefore, std::string letterAfter);
        bool tripleLetterCheck(std::string name);
        bool checkLevenshtein(std::string name);

        std::string toCyrilic(std::string name);
};

#endif // NAME_GEN_H_INCLUDED
