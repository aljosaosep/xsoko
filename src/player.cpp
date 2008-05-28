/*
  codename: Pac-Game
  Aljosa Osep 2007
*/
#include "entities.h"

namespace PacGame
{
          namespace GameClasses
          {
			  PPlayer::PPlayer() {}

			  PPlayer::PPlayer(uint8_t _bombs, uint8_t _keys)
			  {
				  bombs = _bombs;
				  keys = _keys;
			  }

			  // setters
			  void PPlayer::setBombs(uint8_t _bombs)
			  {
				  bombs = _bombs;
			  }

			  void PPlayer::setKeys(uint8_t _keys)
			  {
				  keys = _keys;
			  }

			  // getters
			  int PPlayer::getScore()
			  {
				  return score;
			  }

			  unsigned short PPlayer::getBombs()
			  {
				  return (unsigned short)bombs;
			  }

			  unsigned short PPlayer::getKeys()
			  {
				  return (unsigned short)keys;
			  }

			  // increase +1
			  void PPlayer::incScore()
			  {
				  score++;
			  }

			  void PPlayer::incBombs()
			  {
				  bombs++;
			  }

			  void PPlayer::incKeys()
			  {
				  keys++;
			  }

			  // ===== FUNCTIONS TO OVERRIDE ===== //
			  void PPlayer::onDeath()
			  {
				  // TODO
			  }

			  void PPlayer::draw() 
			  {
				  // TODO
			  }

			  bool PPlayer::initialize()
			  {
				  // TODO
				  return 0;
			  }

			  void PPlayer::print()
			  {
				  // TODO
				  cout<<"==== PLAYER INFO ===="<<endl;
				  cout<<"Bombs:" <<getBombs()<<endl;
				  cout<<"Score:" <<getScore()<<endl;
				  cout<<"Keys:" <<getKeys()<<endl;
				  cout<<"x: "<<getCoordX()<<"  "<<"y: "<<getCoordY()<<endl;
				  cout<<"====================="<<endl;
			  }
          }
}
