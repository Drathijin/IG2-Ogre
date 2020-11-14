#include "Aspas.h"
#include "IG2App.h"

//clase Aspa y AspasMolino


int Aspa::id = 0;
Aspa::Aspa(Ogre::SceneManager* sm, Nodo* parent) :
	EntidadIG(parent->createChildSceneNode())
{
	tableroNode = mNode->createChildSceneNode("tablero_" + std::to_string(Aspa::id));
	Ogre::Entity* ent = mSM->createEntity("cube.mesh");
	ent->setMaterialName("Aspas/Tabla");
	tableroNode->attachObject(ent);
	tableroNode->setScale({ 0.1, 1, 0.1 });
	tableroNode->setPosition(0, -60, 0);
	cilindroNode = mNode->createChildSceneNode("adorno_" + std::to_string(Aspa::id));
	ent = mSM->createEntity("Barrel.mesh");
	ent->setMaterialName("Aspas/Adorno");
	cilindroNode->attachObject(ent);
	cilindroNode->setPosition(0, -100, 5);
	addID();
}


int AspasMolino::count = 0;
AspasMolino::AspasMolino(int n, bool flag, Nodo* parent, float speed)
	: EntidadIG(parent->createChildSceneNode()), rSpeed(speed)
{
	numAspas = n;
	savedInArray = flag;
	std::string name = "aspasMolino" + AspasMolino::count;
	//Para el enunciado 4 5 6
	if (!savedInArray)
	{
		for (int i = 0; i < numAspas; i++)
		{
			Aspa a = Aspa(mSM, mNode);
			a.getNode()->roll(Ogre::Angle(i * (360 / numAspas)));
			a.cilindroNode->roll(Ogre::Angle(-i * (360 / numAspas)));
		}
	}
	//Para el enunciado 7 8 
	else
	{
		arrayAspas = new Aspa * [numAspas];
		for (int i = 0; i < numAspas; i++)
		{
			arrayAspas[i] = new Aspa(mSM, mNode);
			arrayAspas[i]->getNode()->roll(Ogre::Angle(i * (360 / numAspas)));
			arrayAspas[i]->cilindroNode->roll(Ogre::Angle(-i * (360 / numAspas)));
		}
	}
	helpers::createEntity(mSM, botoncicoNode, "boton" + AspasMolino::count, "Barrel.mesh", parent, "Aspas/Botoncico")->pitch(Ogre::Degree(90));
	botoncicoNode->scale({ 5, 1.5, 5 });
	botoncicoNode->setPosition({ 0, 0, 10 });//ok
	AspasMolino::count++;
}

bool AspasMolino::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_g)
	{
		girarAspas();
	}
	else if (evt.keysym.sym == SDLK_r)
	{
		if (savedInArray)
		{
			for (int i = 0; i < numAspas; i++)
				arrayAspas[i]->cilindroNode->setVisible(false);
		}
		else
		{
			for (int i = 0; i < numAspas; i++)
				mSM->getSceneNode("adorno_" + std::to_string(i))->setVisible(false);
		}
	}
	return 1;
}

void AspasMolino::girarAspas(float delta)
{
	mNode->roll(Ogre::Degree(rSpeed * delta));

	if (savedInArray)
	{
		for (int i = 0; i < numAspas; i++)
			arrayAspas[i]->cilindroNode->roll(Ogre::Degree(-rSpeed * delta), Ogre::Node::TS_PARENT);
	}
	else
	{
		for (int i = 0; i < numAspas; i++)
			mSM->getSceneNode("adorno_" + std::to_string(i))->roll(Ogre::Degree(-rSpeed * delta));
	}
}