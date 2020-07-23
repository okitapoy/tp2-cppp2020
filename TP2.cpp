

#include "DocumentXML.hpp"
#include "ElementXML.hpp"
#include "Histoire.hpp"
#include "Lecteur.hpp"

//#include "arbreavl.h"
//#include "arbremap.h"
#include "arbreMapAvl.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>



using namespace std;

void genererArbreFrequence(const vector<Histoire *> *histoires, ArbreMapAVL<string,int> *&avl,ArbreMapAVL<int,string> &arbreTitres);
void genererArbreIDF(int nbrHistoires, ArbreMapAVL<string,int> *&avl, ArbreMapAVL<string,double> &arbreIDF);
void appliquerFormulerIDF(ArbreMapAVL<string,double> &arbreIDF, int nbrHistoires);


vector< Histoire * > *
lireDocuments( string a_nomFichier )
{
    vector< Histoire * > * histoires = new vector< Histoire * >();
    DocumentXML * listeFichiers = lireFichierXML( a_nomFichier );

    assert( nullptr != listeFichiers );
    ElementXML * courant = listeFichiers->racine();
    assert( nullptr != courant );

    courant = courant->prochainElement();

    assert( nullptr != courant );
    for( NoeudXML * contenu : * courant )
    {
        assert( nullptr != contenu );
        if( contenu->estElement() )
        {
            ElementXML * element = ( ElementXML * )contenu;

            assert( nullptr != element );
            DocumentXML * doc = lireFichierXML( element->attribut( string( "fichier" ) ) );

            assert( nullptr != doc );
            vector< Histoire * > * h = extraireHistoires( * doc );

            assert( nullptr != h );
            assert( nullptr != histoires );
            histoires->insert( histoires->end(), h->begin(), h->end() );
        }
    }

    return histoires;
}




//--------------------------------------------------------------
//----------------------------------------------------------------


void genererArbreFrequence(const vector<Histoire *> *histoires, ArbreMapAVL<string,int> *&avl,ArbreMapAVL<int,string> &arbreTitres){


  int tempChiffre = 0;
  int index = 0;

    for( Histoire * histoire : * histoires )
    {
        arbreTitres.inserer(index,histoire->titre());
        avl[index] = ArbreMapAVL<string,int>();

        for( Phrase p : * histoire )
        {

          for(auto iterPhrase = p.begin(); iterPhrase != p.end(); ++iterPhrase){
            string mot =  *iterPhrase;


            if(avl[index].contient(mot)){
              tempChiffre =  avl[index].operator[](mot) + 1;
              avl[index].inserer(mot,tempChiffre);

            }else{
              avl[index].inserer(mot,1);
            }

         }

        }
        ++index;
    }


}



void genererArbreIDF(int nbrHistoires, ArbreMapAVL<string,int> *&avl, ArbreMapAVL<string,double> &arbreIDF){

  string mot;
  double nbrOccurence = 0;

  //int c = 0;//====

  for(int i = 0; i < nbrHistoires; i++){

    if(i == 0){

      for(auto iter = avl[i].debut(); iter != avl[i].fin(); ++iter){
          mot =  avl[i].operator[](iter);
          arbreIDF.inserer(mot,1.0);
      }

    }else{
      for(auto iter = avl[i].debut(); iter != avl[i].fin(); ++iter){

        mot =  avl[i].operator[](iter);

        if(arbreIDF.contient(mot)){
          nbrOccurence = arbreIDF.operator[](mot) + 1;
          arbreIDF.inserer(mot,nbrOccurence);
        }else{
          arbreIDF.inserer(mot,1.0);
        }

      }

    }

  }

  appliquerFormulerIDF(arbreIDF,nbrHistoires);


}


void appliquerFormulerIDF(ArbreMapAVL<string,double> &arbreIDF, int nbrHistoires){

  string mot;
  double cc = 0;
  double idf = 0;
  for(auto iter = arbreIDF.debut(); iter != arbreIDF.fin(); ++iter){
    mot = arbreIDF.operator[](iter);
    cc = arbreIDF.operator[](mot);
    idf = log2(nbrHistoires/cc);
    arbreIDF.inserer(mot,idf);


    cc = arbreIDF.operator[](mot);
   cout << mot << " : " << cc << endl;

  }
}








int main() {
    // gardez la ligne suivante, elle lit le corpus et le place dans la structure de base.
    // Vous avez donc un vecteur d'histoire qui contient l'information sur les histoires,
    // les Phrases et les mots qu'elles contiennent.		arbreavl.o
    vector< Histoire * > * histoires = lireDocuments( string( "listeDocument.xml" ) );

  ArbreMapAVL<string,int> *avl = new ArbreMapAVL<string,int>[histoires->size()];
  ArbreMapAVL<int,string> arbreTitres;
  ArbreMapAVL<string,double> arbreIDF;

  genererArbreFrequence(histoires,avl,arbreTitres);
  genererArbreIDF(histoires->size(),avl,arbreIDF);


  /*
  int tempChiffre = 0;
  int index = 0;

    // Pour votre projet, enlevez le code qui suit et remplacer le par votre code.
    // vous pouvez ajouter des fonctionions.

    // Parcourir les histoires a l'aide de l'iterateur du vecteur.
    for( Histoire * histoire : * histoires )
    {
        // Les histoires ont une variable de classe 'titre'.
        //cout << histoire->titre() << endl;
      //  cout << "index  : " << index << endl;
        arbreTitres.inserer(index,histoire->titre());
        avl[index] = ArbreMapAVL<string,int>();
      //  cout << "rien" << endl;

        // Parcourir les Phrases qui compose une histoire � l'aide de l'iterateur des Histoires.
        for( Phrase p : * histoire )
        {
            // p.begin() va chercher le premier mot de la Phrase p.  c'est aussi un iterateur et il peut
            // s'utiliser avec les for augment�s.
            // ici, nous affichons seulement le premier mot de la Phrase.
          //  cout< *( p.begin() ) << endl;



          for(auto iterPhrase = p.begin(); iterPhrase != p.end(); ++iterPhrase){
            string mot =  *iterPhrase;


            if(avl[index].contient(mot)){
              tempChiffre =  avl[index].operator[](mot) + 1;
              avl[index].inserer(mot,tempChiffre);

            }else{
              avl[index].inserer(mot,1);
            }

         }

        }

        //cout << endl;
        //break;
        ++index;
    }

*/
//---------------------------------------------------------------------
//--------------------------------------------------------------------


/*

//ArbreMapAVL<string,double> arbreIDF;
string mot;
double nbrOccurence = 0;

//int c = 0;//====

for(int i = 0; i < histoires->size(); i++){

  if(i == 0){

    for(auto iter = avl[i].debut(); iter != avl[i].fin(); ++iter){
        mot =  avl[i].operator[](iter);
        arbreIDF.inserer(mot,1.0);
    }

  }else{
    for(auto iter = avl[i].debut(); iter != avl[i].fin(); ++iter){

      mot =  avl[i].operator[](iter);

      if(arbreIDF.contient(mot)){
        nbrOccurence = arbreIDF.operator[](mot) + 1;
        arbreIDF.inserer(mot,nbrOccurence);
      }else{
        arbreIDF.inserer(mot,1.0);
      }

    }

  }

}
*/




/*
//apliquer la formule log sur arbre idf
string mot;
double cc = 0;
double idf = 0;
for(auto iter = arbreIDF.debut(); iter != arbreIDF.fin(); ++iter){
  mot = arbreIDF.operator[](iter);
  cc = arbreIDF.operator[](mot);
  idf = log2(histoires->size()/cc);
  arbreIDF.inserer(mot,idf);


  cc = arbreIDF.operator[](mot);
 cout << mot << " : " << cc << endl;

}

*/




//cout << "log : " << log2(26.0/7.0) << endl;



    return 0;



    /*the hideous monster
    launched itself into the air straight toward them. (_To be concluded in the February
    Number._) </chapitre> */
    //3
    //2
    //1
    //zero = 7
}
