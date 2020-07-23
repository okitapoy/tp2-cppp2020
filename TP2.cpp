

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


int main() {
    // gardez la ligne suivante, elle lit le corpus et le place dans la structure de base.
    // Vous avez donc un vecteur d'histoire qui contient l'information sur les histoires,
    // les Phrases et les mots qu'elles contiennent.		arbreavl.o
    vector< Histoire * > * histoires = lireDocuments( string( "listeDocument.xml" ) );


  //  cout << "size : " << histoires->size() << endl;

//ArbreMap<string, int> *mapTest = new ArbreMap<string, int>[histoires->size()];

//ArbreMapAVL<string,int> *avl = new ArbreMapAVL<string,int>[histoires->size()];

//avl.inserer("un",11);
//avl.inserer("deux",22);
//avl.inserer("trois",33);
//avl.inserer("quatre",44);

//ArbreAVL<int>::Iterateur iter;iterer
//ArbreMap<string, int>::Iterateur iter(avl);// = avl.rechercher(1);

//ArbreMapAVL<string, int>::Iterateur iterer = avl.debut();

//ArbreMapAVL<string, int>::Iterateur it = avl.rechercher("un");
//string cle = avl.operator[](iterer);

//if(it){
//  cout << "iter a fonctionnner" << endl;
//}
//cout << avl.operator[](cle) << endl;



//if(avl.contient("trois")){
//  Noeud noeud("trois",3333);
//cout << avl.operator[]("trois") << endl;
//avl.inserer("trois",3333339);
//}






  //  exit(-1);




  //   vector<string>::const_iterator iterPhrase;
  ArbreMapAVL<string,int> *avl = new ArbreMapAVL<string,int>[histoires->size()];
  int tempChiffre = 0;
  int index = 0;

cout << "size : " <<  histoires->size() << endl;
    // Pour votre projet, enlevez le code qui suit et remplacer le par votre code.
    // vous pouvez ajouter des fonctionions.

    // Parcourir les histoires a l'aide de l'iterateur du vecteur.
    for( Histoire * histoire : * histoires )
    {
        // Les histoires ont une variable de classe 'titre'.
        //cout << histoire->titre() << endl;
        cout << "index  : " << index << endl;
        avl[index] = ArbreMapAVL<string,int>();
        cout << "rien" << endl;

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


//test affiche arbre
//ArbreMapAVL<string, int>::Iterateur iterer = avl.debut();
//cout << avl.operator[](iterer) << endl;

//ArbreMapAVL<string, int>::Iterateur it = avl.rechercher("a");
int cle = avl[25].operator[]("is");
cout << cle << endl;

/*
for(auto iterer = avl.debut(); iterer != avl.fin(); ++iterer){
  string cle = avl.operator[](iterer);
  int nombre = avl.operator[](cle);

  cout << cle << " : " << nombre << endl;

}*/


    return 0;



    /*the hideous monster
    launched itself into the air straight toward them. (_To be concluded in the February
    Number._) </chapitre> */
}
