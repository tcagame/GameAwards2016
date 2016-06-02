#include "Viewer.h"
#include "Framework.h"
#include "App.h"
#include "Powerplant.h"
#include "Chargers.h"
#include "Charger.h"
#include "Bases.h"
#include "Base.h"
#include "Bulletin.h"
#include "Bulletins.h"
#include "Refinery.h"
#include "Refineries.h"
#include "GoldMines.h"
#include "GoldMine.h"
#include "mathmatics.h"
#include "Map.h"
#include "Line.h"
#include "Coord.h"
#include "Chip.h"
#include "Ratio.h"
#include "Mouse.h"
#include "Drawer.h"

static const int POWERPLANT_OFFSET_X = -32;
static const int CHARGER_OFFSET_X = -32;
static const int BASE_OFFSET_X = -32;
static const int REFINERY_OFFSET_X = -32;
static const int BULLETIN_OFFSET_X = -32;
static const int PACKET_OFFSET = -8;
static const int CHIP_SIZE = 32;

enum RES {
	RES_NONE,
	RES_POWERPLANT, 
	RES_CHARGER,    
	RES_REFINERY,    
	RES_BASE,    
	RES_BULLETIN,
	RES_GOLD_MINE,
	RES_LINE_NORMAL,
	RES_LINE_CIRCUIT,
	RES_LINE_GUIDEPOINT,
	RES_LINE_DELETE,
	RES_PACKET,
	RES_GROUND,
	MAX_RES,
};

ViewerPtr Viewer::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< Viewer >( fw->getTask( getTag( ) ) );
}

Viewer::Viewer( ) {
	
}

Viewer::~Viewer( ) {
}

void Viewer::initialize( ) {
	DrawerPtr drawer = Drawer::getTask( );
	drawer->load( RES_LINE_NORMAL    , "../resource/line_normal.png" );
	drawer->load( RES_LINE_CIRCUIT   , "../resource/line_circuit.png" );
	drawer->load( RES_POWERPLANT     , "../resource/powerplant.png" );
	drawer->load( RES_CHARGER        , "../resource/charger.png" );
	drawer->load( RES_REFINERY       , "../resource/refinery.png" );
	drawer->load( RES_BASE			 , "../resource/base.png" );
	drawer->load( RES_BULLETIN       , "../resource/bulletin.png" );
	drawer->load( RES_GOLD_MINE      , "../resource/GoldMine.png" );
	drawer->load( RES_LINE_GUIDEPOINT, "../resource/line_guide_point.png" );
	drawer->load( RES_GROUND         , "../resource/ground.png" );
	drawer->load( RES_LINE_DELETE    , "../resource/line_delete.png" );
	drawer->load( RES_PACKET		 , "../resource/star.png" );

	_click_left = CLICK_NONE;
	_click_right = CLICK_NONE;
}

void Viewer::update( ) {
	updateClick( );

	drawGround( );
	drawPowerplant( );
	drawChargers( );
	drawBases( );
	drawRefineries( );
	drawBulletins( );
	drawGoldMines( );
	drawLine( ); // ƒ‰ƒCƒ“‚ª‰æ–Ê‚É•\Ž¦‚³‚ê‚Ä‚¢‚È‚¢‚Ì‚Å‚±‚±‚àŠÖŒW‚È‚¢
	drawGuidFacility( );
	drawGuideLine( );
	drawPacketAnimation( );

	reflesh( );
}

void Viewer::reflesh(  ) {
	_guide = GUIDE_NONE;
}

Coord Viewer::getClickCoord( ) const {
	return _click_coord;
}

Viewer::CLICK Viewer::getClickLeft( ) const {
	return _click_left;
}

Viewer::CLICK Viewer::getClickRight( ) const{
	return _click_right;
}

void Viewer::updateClick( ) {
	MousePtr mouse = Mouse::getTask( );

	if ( mouse->isHoldLeftButton( ) ) {
		if ( _click_left == CLICK_PUSH ||
			 _click_left == CLICK_HOLD ) {
			_click_left = CLICK_HOLD;
		} else {
			_click_left = CLICK_PUSH;
		}
	} else {
		if ( _click_left == CLICK_RELEASE ||
			 _click_left == CLICK_NONE ) {
			_click_left = CLICK_NONE;
		} else {
			_click_left = CLICK_RELEASE;
		}
	}
	if ( mouse->isHoldRightButton( ) ) {
		if ( _click_right == CLICK_PUSH ||
			 _click_right == CLICK_HOLD ) {
			_click_right = CLICK_HOLD;
		} else {
			_click_right = CLICK_PUSH;
		}
	} else {
		if ( _click_right == CLICK_RELEASE ||
			 _click_right == CLICK_NONE ) {
			_click_right = CLICK_NONE;
		} else {
			_click_right = CLICK_RELEASE;
		}
	}

	Vector pos = mouse->getPos( );
	_click_coord = Coord( ( int )pos.x / CHIP_SIZE, ( int )pos.y / CHIP_SIZE );
}

void Viewer::drawGround( ) {
	DrawerPtr drawer = Drawer::getTask( );
	for ( int j = 0; j < COORD_HEIGHT; j++ ) {
		for ( int i = j % 2; i < COORD_WIDTH; i += 2 ) {
			Drawer::Sprite sprite( Drawer::Transform( i * CHIP_SIZE - CHIP_SIZE, j * CHIP_SIZE ), RES_GROUND );
			drawer->set( sprite );
		}
	}
}

void Viewer::drawPowerplant( ) const {
	AppPtr app = App::getTask( );
	if ( !app ) {
		return;
	}
	PowerplantConstPtr powerplant = app->getPowerplant( );
	Coord coord = powerplant->getCoord( );

	int sx = coord.x * CHIP_SIZE + POWERPLANT_OFFSET_X;
	int sy = coord.y * CHIP_SIZE;
	Drawer::Sprite sprite( Drawer::Transform( sx, sy ), RES_POWERPLANT );
	DrawerPtr drawer = Drawer::getTask( );
	drawer->set( sprite );
}

void Viewer::drawChargers( ) const {
	AppPtr app = App::getTask( );
	if ( !app ) {
		return;
	}
	ChargersConstPtr chargers = app->getChargers( );
	const int size = chargers->getSize( );
	for ( int i = 0; i < size; i++ ) {
		ChargerConstPtr charger = std::dynamic_pointer_cast< const Charger >( chargers->get( i ) );
		Coord coord = charger->getCoord( );
		int sx = coord.x * CHIP_SIZE + CHARGER_OFFSET_X;
		int sy = coord.y * CHIP_SIZE;
		DrawerPtr drawer = Drawer::getTask( );
		drawer->set( Drawer::Sprite( Drawer::Transform( sx, sy ), RES_CHARGER ) );
	}

}

void Viewer::drawBases( ) const {
	AppPtr app = App::getTask( );
	if ( !app ) {
		return;
	}
	BasesConstPtr bases = app->getBases( );
	const int size = bases->getSize( );
	for ( int i = 0; i < size; i++ ) {
		BaseConstPtr base = std::dynamic_pointer_cast< const Base >( bases->get( i ) );
		Coord coord = base->getCoord( );
		int sx = coord.x * CHIP_SIZE + BASE_OFFSET_X;
		int sy = coord.y * CHIP_SIZE;
		DrawerPtr drawer = Drawer::getTask( );
		drawer->set( Drawer::Sprite( Drawer::Transform( sx, sy ), RES_BASE ) );
	}
}

void Viewer::drawRefineries( ) const {
	AppPtr app = App::getTask( );
	if ( !app ) {
		return;
	}
	RefineriesConstPtr refineries = app->getRefineries( );
	const int size = refineries->getSize( );
	for ( int i = 0; i < size; i++ ) {
		RefineryConstPtr refinery = std::dynamic_pointer_cast< const Refinery >( refineries->get( i ) );
		Coord coord = refinery->getCoord( );
		int sx = coord.x * CHIP_SIZE + REFINERY_OFFSET_X;
		int sy = coord.y * CHIP_SIZE;
		DrawerPtr drawer = Drawer::getTask( );
		drawer->set( Drawer::Sprite( Drawer::Transform( sx, sy ), RES_REFINERY ) );
	}
}

void Viewer::drawBulletins( ) const {
	AppPtr app = App::getTask( );
	if ( !app ) {
		return;
	}
	BulletinsConstPtr bulletins = app->getBulletins( );
	const int size = bulletins->getSize( );
	for ( int i = 0; i < size; i++ ) {
		BulletinConstPtr bulletin = std::dynamic_pointer_cast< const Bulletin >( bulletins->get( i ) );
		Coord coord = bulletin->getCoord( );
		int sx = coord.x * CHIP_SIZE + BULLETIN_OFFSET_X;
		int sy = coord.y * CHIP_SIZE;
		DrawerPtr drawer = Drawer::getTask( );
		drawer->set( Drawer::Sprite( Drawer::Transform( sx, sy ), RES_BULLETIN ) );
	}
}

void Viewer::drawGuidFacility( ) const {
	if ( _guide == GUIDE_NONE ) {
		return;
	}

	int sx = _coord_guid.x * CHIP_SIZE;
	int sy = _coord_guid.y * CHIP_SIZE;
	RES res = RES_NONE;

	switch ( _guide ) {
	case GUIDE_CHARGER:
		sx += CHARGER_OFFSET_X;
		res = RES_CHARGER;
		break;
	case GUIDE_BASE:
		sx += BASE_OFFSET_X;
		res = RES_BASE;
		break;
	case GUIDE_REFINERY:
		sx += REFINERY_OFFSET_X;
		res = RES_REFINERY;
		break;
	case GUIDE_BULLETIN:
		sx += BULLETIN_OFFSET_X;
		res = RES_BULLETIN;
		break;
	}

	DrawerPtr drawer = Drawer::getTask( );
	drawer->set( Drawer::Sprite( Drawer::Transform( sx, sy ), res, Drawer::BLEND_ALPHA, 0.5  ) );
}

void Viewer::drawLine( ) const {
	AppPtr app = App::getTask( );
	if ( !app ) {
		return;
	}

	LineConstPtr line = app->getLine( );
	const Line::Data data = line->getData( );

	DrawerPtr drawer = Drawer::getTask( );
	for ( int i = 0; i < COORD_WIDTH; i++ ) {
		for ( int j = 0; j < COORD_HEIGHT; j++ ) {
			Line::Data::Chip chip = data.array[ i + j * COORD_WIDTH ];
			if ( chip.guide ) {
				continue;
			}
			int idx = convLineTypeToIdx( chip.form_dir );
			if ( idx < 0 ) {
				continue;
			}
			int sx = i * CHIP_SIZE;
			int sy = j * CHIP_SIZE;
			int tx = idx % 4 * CHIP_SIZE;
			int ty = idx / 4 * CHIP_SIZE;
			if ( chip.circuit_dir == Line::DIR_NONE ) {
				drawer->set( Drawer::Sprite( Drawer::Transform( sx, sy, tx, ty, CHIP_SIZE, CHIP_SIZE ), RES_LINE_NORMAL ) );
			} else {
				drawer->set( Drawer::Sprite( Drawer::Transform( sx, sy, tx, ty, CHIP_SIZE, CHIP_SIZE ), RES_LINE_CIRCUIT ) );
			}
		}
	}
}

void Viewer::drawGuideLine( ) const {
	AppPtr app = App::getTask( );
	if ( !app ) {
		return;
	}

	LineConstPtr line = app->getLine( );
	if ( !line->isGuiding( ) ) {
		return;
	}

	DrawerPtr drawer = Drawer::getTask( );
	const Line::Data data = line->getData( );
	for ( int i = 0; i < COORD_WIDTH; i++ ) {
		for ( int j = 0; j < COORD_HEIGHT; j++ ) {
			Line::Data::Chip chip = data.array[ i + j * COORD_WIDTH ];
			if ( !chip.guide ) {
				continue;
			}
			int idx = convLineTypeToIdx( chip.form_dir );
			if ( idx < 0 ) {
				continue;
			}
			int sx = i * CHIP_SIZE;
			int sy = j * CHIP_SIZE;
			int tx = idx % 4 * CHIP_SIZE;
			int ty = idx / 4 * CHIP_SIZE;
			if ( app->isModeDeleteLine( ) ) {
				drawer->set( Drawer::Sprite( Drawer::Transform( sx, sy, tx, ty, CHIP_SIZE, CHIP_SIZE ),
					RES_LINE_DELETE ) );
			} else {
				drawer->set( Drawer::Sprite( Drawer::Transform( sx, sy, tx, ty, CHIP_SIZE, CHIP_SIZE ),
					RES_LINE_NORMAL, Drawer::BLEND_ALPHA, 0.5 ) );
			}
		}
	}

	{
		int sx = _click_coord.x * CHIP_SIZE;
		int sy = _click_coord.y * CHIP_SIZE;
		drawer->set( Drawer::Sprite( Drawer::Transform( sx, sy ), RES_LINE_GUIDEPOINT ) );
	}
}

void Viewer::drawGoldMines( ) const {
	AppPtr app = App::getTask( );
	if ( !app ) {
		return;
	}
	GoldMinesConstPtr gold_mines = app->getGoldMines( );
	const int size = gold_mines->getSize( );
	for ( int i = 0; i < size; i++ ) {
		GoldMineConstPtr gold_mine = std::dynamic_pointer_cast< const GoldMine >( gold_mines->get( i ) );
		int sx = gold_mine->getCoord( ).x * CHIP_SIZE;
		int sy = gold_mine->getCoord( ).y * CHIP_SIZE;
		DrawerPtr drawer = Drawer::getTask( );
		drawer->set( Drawer::Sprite( Drawer::Transform( sx, sy ), RES_GOLD_MINE ) );
	}
}

void Viewer::drawPacketAnimation( ) const {
	AppPtr app = App::getTask( );
	if ( !app ) {
		return;
	}

	LineConstPtr line = app->getLine( );
	const Line::Data& data = line->getData( );
	int length = data.packet_ratio.cal( CHIP_SIZE );

	DrawerPtr drawer = Drawer::getTask( );
	for ( int i = 0; i < COORD_WIDTH; i++ ) {
		for ( int j = 0; j < COORD_HEIGHT; j++ ) {
			Line::Data::Chip chip = data.array[ i + j * COORD_WIDTH ];
			if ( chip.guide || chip.circuit_dir == Line::DIR_NONE ) {
				continue;
			}

			int offset_x = 0;
			int offset_y = 0;
			unsigned char start_dir = ~chip.circuit_dir & chip.form_dir;
			switch( start_dir ) {
			case Line::DIR_U___:
				offset_y = PACKET_OFFSET * 3;
				offset_x = PACKET_OFFSET;
				break;
			case Line::DIR__D__:
				offset_y = -PACKET_OFFSET;
				offset_x = PACKET_OFFSET;
				break;
			case Line::DIR___L_:
				offset_x = PACKET_OFFSET * 3;
				offset_y = PACKET_OFFSET;
				break;
			case Line::DIR____R:
				offset_x = -PACKET_OFFSET;
				offset_y = PACKET_OFFSET;
				break;
			default:
				break;
			}

			int sx = i * CHIP_SIZE + offset_x;
			int sy = j * CHIP_SIZE + offset_y;
			int animation_sx = sx;
			int animation_sy = sy;
			unsigned char advance_dir;
			bool is_reverse = false;
			switch( chip.form_dir ) {
			case Line::DIR_UD__: 
			case Line::DIR___LR:
				advance_dir = chip.circuit_dir;
				break;
			case Line::DIR_U_L_: 
			case Line::DIR_U__R: 
			case Line::DIR__DL_: 
			case Line::DIR__D_R:
				advance_dir = reverseDir( start_dir );
				is_reverse = true;
				break;
			default:
				break;
			}

			if( ( length < CHIP_SIZE / 2 || !is_reverse ) ) {
				if ( advance_dir & Line::DIR_U___ ) {
					animation_sy -= length;
				}
				if ( advance_dir & Line::DIR__D__ ) {
					animation_sy += length;
				}
				if ( advance_dir & Line::DIR___L_ ) {
					animation_sx -= length;
				}
				if ( advance_dir & Line::DIR____R ) {
					animation_sx += length;
				}
			} else {
				if ( start_dir & Line::DIR_U___ ) {
					animation_sy += CHIP_SIZE / 2;
				}
				if ( start_dir & Line::DIR__D__ ) {
					animation_sy -= CHIP_SIZE / 2;
				}
				if ( start_dir & Line::DIR___L_ ) {
					animation_sx += CHIP_SIZE / 2;
				}
				if ( start_dir & Line::DIR____R ) {
					animation_sx -= CHIP_SIZE / 2;
				}
				if ( chip.circuit_dir & Line::DIR_U___ ) {
					animation_sy -= length - CHIP_SIZE / 2;
				}
				if ( chip.circuit_dir & Line::DIR__D__ ) {
					animation_sy += length - CHIP_SIZE / 2;
				}
				if ( chip.circuit_dir & Line::DIR___L_ ) {
					animation_sx -= length - CHIP_SIZE / 2;
				}
				if ( chip.circuit_dir & Line::DIR____R ) {
					animation_sx += length - CHIP_SIZE / 2;
				}
			}
	
			drawer->set( Drawer::Sprite( Drawer::Transform( animation_sx, animation_sy ), RES_PACKET ) );
		}
	}
}

unsigned char Viewer::reverseDir( unsigned char start_dir ) const {
	switch ( start_dir ) {
	case Line::DIR_U___:
		return Line::DIR__D__;
		break;
	case Line::DIR__D__:
		return Line::DIR_U___;
		break;
	case Line::DIR___L_:
		return Line::DIR____R;
		break;
	case Line::DIR____R:
		return Line::DIR___L_;
		break;
	default:
		return -1;
		break;
	}
}

void Viewer::setGuidFacility( const Coord& coord, GUIDE guide ) {
	_coord_guid = coord;
	_guide = guide;
}

int Viewer::convLineTypeToIdx( unsigned char dir ) const {
	switch ( dir ) {
	case Line::DIR___LR:
		return 0;
		break;
	case Line::DIR_UD__:
		return 1;
		break;
	case Line::DIR_U__R:
		return 2;
		break;
	case Line::DIR_U_L_:
		return 3;
		break;
	case Line::DIR__D_R:
		return 4;
		break;
	case Line::DIR__DL_:
		return 5;
		break;
	case Line::DIR_U_LR:
		return 6;
		break;
	case Line::DIR__DLR:
		return 7;
		break;
	case Line::DIR_UD_R:
		return 8;
		break;
	case Line::DIR_UDL_:
		return 9;
		break;
	case Line::DIR_UDLR:
		return 10;
		break;
	default:
		return -1;
		break;
	}

}