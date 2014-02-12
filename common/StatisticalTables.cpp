// Copyright (C) 2005 Daniel Dalevi
// Distributed under the GNU GENERAL PUBLIC LICENSE version 2

#include "StatisticalTables.h"

using namespace std;

double StatisticalTables::quantileChiSquare( const int& r, const double& sig) 
{
  int ia = -1;  	
  vector<double> val;

  if( sig == 0.05 )
    {
      ia = 0;
      val.push_back( static_cast<double>( -1.0 ) );
    }
  else if( sig == 0.01 )
    {
      ia = 1;
      val.push_back( static_cast<double>( -1.0 ) );
    }
  else if( sig == 0.001 )
    {
      ia = 2;
      val.push_back( static_cast<double>( -1.0 ) );
    }
  else 
    {
      cerr << sig << ": not defined in table. sig=0.05 will be used!" << endl;
      ia = 0;
    }
  

  switch( r )
    {
    case 1:
      val[ 0 ] = 3.841; val[ 1 ] = 6.64; val[ 2 ] = 10.83;
      break;
    case 2:
      val[ 0 ] = 5.99; val[ 1 ] = 9.21; val[ 2 ] = 13.82;
      break;
    case 3: 
      val[ 0 ] = 7.815; val[ 1 ] = 11.35; val[ 2 ] = 16.27;
      break;
    case 4:
      val[ 0 ] = 9.49; val[ 1 ] = 13.28; val[ 2 ] = 18.47;
      break;
    case 5:
      val[ 0 ] = 11.0; val[ 1 ] = 15.09; val[ 2 ] = 20.52;
      break;
    case 6:
      val[ 0 ] = 12.5; val[ 1 ] = 16.81; val[ 2 ] = 22.46;
      break;
    case 7:
      val[ 0 ] = 14.0; val[ 1 ] = 18.48; val[ 2 ] = 24.32;
      break;
    case 8:
      val[ 0 ] = 15.5; val[ 1 ] = 20.09; val[ 2 ] = 26.13;
      break;
    case 9:
      val[ 0 ] = 16.9; val[ 1 ] = 21.67; val[ 2 ] = 27.88;
      break;
    case 10:
      val[ 0 ] = 18.3; val[ 1 ] = 23.21; val[ 2 ] = 29.59;
      break;
    case 11:
      val[ 0 ] = 19.6; val[ 1 ] = 24.73; val[ 2 ] = 31.26;
      break;
    case 12:
      val[ 0 ] = 21.0; val[ 1 ] = 26.22; val[ 2 ] = 32.91;
      break;
    case 13:
      val[ 0 ] = 22.3; val[ 1 ] = 27.69; val[ 2 ] = 34.53;
      break;
    case 14:
      val[ 0 ] = 23.6; val[ 1 ] = 29.14; val[ 2 ] = 36.12;
      break;
    case 15:
      val[ 0 ] = 25.0; val[ 1 ] = 30.58; val[ 2 ] = 37.70;
      break;
    case 16:
      val[ 0 ] = 26.3; val[ 1 ] = 32.00; val[ 2 ] = 39.25;
      break;
    case 17:
      val[ 0 ] = 27.5; val[ 1 ] = 33.41; val[ 2 ] = 40.79;
      break;
    case 18:
      val[ 0 ] = 28.8; val[ 1 ] = 34.81; val[ 2 ] = 42.31;
      break;
    case 19:
      val[ 0 ] = 30.14; val[ 1 ] = 36.19; val[ 2 ] = 43.82;
      break;
    case 20:
      val[ 0 ] = 31.4; val[ 1 ] = 37.57; val[ 2 ] = 45.32;
      break;
    case 21:
      val[ 0 ] = 32.6; val[ 1 ] = 38.93; val[ 2 ] = 46.80;
      break;
    case 22:
      val[ 0 ] = 33.9; val[ 1 ] = 40.29; val[ 2 ] = 48.27;
      break;
    case 23:
      val[ 0 ] = 35.1; val[ 1 ] = 41.64; val[ 2 ] = 49.73;
      break;
    case 24:
      val[ 0 ] = 36.4; val[ 1 ] = 42.98; val[ 2 ] = 51.18;
      break;
    case 25:
      val[ 0 ] = 37.6; val[ 1 ] = 44.31; val[ 2 ] = 52.62;
      break;
    case 26:
      val[ 0 ] = 38.8; val[ 1 ] = 45.64; val[ 2 ] = 54.05;
      break;
    case 27:
      val[ 0 ] = 40.1; val[ 1 ] = 46.96; val[ 2 ] = 55.48;
      break;
    case 28:
      val[ 0 ] = 41.3; val[ 1 ] = 48.28; val[ 2 ] = 56.89;
      break;
    case 29:
      val[ 0 ] = 42.5; val[ 1 ] = 49.59; val[ 2 ] = 58.30;
      break;
    case 30:
      val[ 0 ] = 43.7; val[ 1 ] = 50.89; val[ 2 ] = 59.70;
      break;
    case 31:
      val[ 0 ] = 44.9; val[ 1 ] = 52.19; val[ 2 ] = 61.10;
      break;
    case 32:
      val[ 0 ] = 46.1; val[ 1 ] = 53.49; val[ 2 ] = 62.49;
      break;
    case 33:
      val[ 0 ] = 47.4; val[ 1 ] = 54.78; val[ 2 ] = 63.87;
      break;
    case 34:
      val[ 0 ] = 48.6; val[ 1 ] = 56.06; val[ 2 ] = 65.25;
      break;
    case 35:
      val[ 0 ] = 49.8; val[ 1 ] = 57.34; val[ 2 ] = 66.62;
      break;
    case 36:
      val[ 0 ] = 51.0; val[ 1 ] = 58.62; val[ 2 ] = 67.99;
      break;
    case 37:
      val[ 0 ] = 52.1; val[ 1 ] = 59.89; val[ 2 ] = 69.35;
      break;
    case 38:
      val[ 0 ] = 53.3; val[ 1 ] = 61.16; val[ 2 ] = 70.71;
      break;
    case 39:
      val[ 0 ] = 54.5; val[ 1 ] = 62.43; val[ 2 ] = 72.06;
      break;
    case 40:
      val[ 0 ] = 55.7; val[ 1 ] = 63.69; val[ 2 ] = 73.41;
      break;
    case 41:
      val[ 0 ] = 56.9; val[ 1 ] = 64.95; val[ 2 ] = 74.75;
      break;
    case 42:
      val[ 0 ] = 58.1; val[ 1 ] = 66.21; val[ 2 ] = 76.09;
      break;
    case 43:
      val[ 0 ] = 59.3; val[ 1 ] = 67.46; val[ 2 ] = 77.42;
      break;
    case 44:
      val[ 0 ] = 60.4; val[ 1 ] = 68.71; val[ 2 ] = 78.75;
      break;
    case 45:
      val[ 0 ] = 61.6; val[ 1 ] = 69.96; val[ 2 ] = 80.08;
      break;
    case 46:
      val[ 0 ] = 62.8; val[ 1 ] = 71.20; val[ 2 ] = 81.40;
      break;
    case 47:
      val[ 0 ] = 64.0; val[ 1 ] = 72.44; val[ 2 ] = 82.72;
      break;
    case 48:
      val[ 0 ] = 65.1; val[ 1 ] = 73.68; val[ 2 ] = 84.03;
      break;
    case 49:
      val[ 0 ] = 66.3; val[ 1 ] = 74.92; val[ 2 ] = 85.35;
      break;
    case 50:
      val[ 0 ] = 67.5; val[ 1 ] = 76.15; val[ 2 ] = 86.66;
      break;
    case 51:
      val[ 0 ] = 68.6; val[ 1 ] = 77.39; val[ 2 ] = 87.97;
      break;
    case 52:
      val[ 0 ] = 69.8; val[ 1 ] = 78.62; val[ 2 ] = 89.27;
      break;
    case 53:
      val[ 0 ] = 70.9; val[ 1 ] = 79.84; val[ 2 ] = 90.57;
      break;
    case 54:
      val[ 0 ] = 72.1; val[ 1 ] = 81.07; val[ 2 ] = 91.88;
      break;
    case 55:
      val[ 0 ] = 73.3; val[ 1 ] = 82.29; val[ 2 ] = 93.17;
      break;
    case 56:
      val[ 0 ] = 74.4; val[ 1 ] = 83.52; val[ 2 ] = 94.47;
      break;
    case 57:
      val[ 0 ] = 75.6; val[ 1 ] = 84.73; val[ 2 ] = 95.75;
      break;
    case 58:
      val[ 0 ] = 76.7; val[ 1 ] = 85.95; val[ 2 ] = 97.03;
      break;
    case 59:
      val[ 0 ] = 77.9; val[ 1 ] = 87.17; val[ 2 ] = 98.34;
      break;
    case 60:
      val[ 0 ] = 79.0; val[ 1 ] = 88.38; val[ 2 ] = 99.62;
      break;
    case 61:
      val[ 0 ] = 80.2; val[ 1 ] = 89.59; val[ 2 ] = 100.88;
      break;
    case 62:
      val[ 0 ] = 81.3; val[ 1 ] = 90.80; val[ 2 ] = 102.15;
      break;
    case 63:
      val[ 0 ] = 82.5; val[ 1 ] = 92.01; val[ 2 ] = 103.46;
      break;
    case 64:
      val[ 0 ] = 83.6; val[ 1 ] = 93.22; val[ 2 ] = 104.72;
      break;
    case 65:
      val[ 0 ] = 84.8; val[ 1 ] = 94.42; val[ 2 ] = 105.97;
      break;
    case 66:
      val[ 0 ] = 85.9; val[ 1 ] = 95.63; val[ 2 ] = 107.26;
      break;
    case 67:
      val[ 0 ] = 87.1; val[ 1 ] = 96.83; val[ 2 ] = 108.54;
      break;
    case 68:
      val[ 0 ] = 88.2; val[ 1 ] = 98.03; val[ 2 ] = 109.79;
      break;
    case 69:
      val[ 0 ] = 89.3; val[ 1 ] = 99.23; val[ 2 ] = 111.06;
      break;
    case 70:
      val[ 0 ] = 90.5; val[ 1 ] = 100.42;val[ 2 ] = 112.31;
      break;
    case 71:
      val[ 0 ] = 91.6; val[ 1 ] = 101.62;val[ 2 ] = 113.56;
      break;
    case 72:
      val[ 0 ] = 92.8; val[ 1 ] = 102.82;val[ 2 ] = 114.84;
      break;
    case 73:
      val[ 0 ] = 93.9; val[ 1 ] = 104.01;val[ 2 ] = 116.08;
      break;
    case 74:
      val[ 0 ] = 95.0; val[ 1 ] = 105.20;val[ 2 ] = 117.35;
      break;
    case 75:
      val[ 0 ] = 96.2; val[ 1 ] = 106.39;val[ 2 ] = 118.60;
      break;
    case 76:
      val[ 0 ] = 97.3; val[ 1 ] = 107.58;val[ 2 ] = 119.85;
      break;
    case 77:
      val[ 0 ] = 98.4; val[ 1 ] = 108.77;val[ 2 ] = 121.11;
      break;
    case 78:
      val[ 0 ] = 99.6; val[ 1 ] = 109.96;val[ 2 ] = 122.36;
      break;
    case 79:
      val[ 0 ] = 100.; val[ 1 ] = 111.15;val[ 2 ] = 123.60;
      break;
    case 80:
      val[ 0 ] = 101.; val[ 1 ] = 112.33;val[ 2 ] = 124.84;
      break;
    case 81:
      val[ 0 ] = 103.; val[ 1 ] = 113.51;val[ 2 ] = 126.09;
      break;
    case 82:
      val[ 0 ] = 104.; val[ 1 ] = 114.70;val[ 2 ] = 127.33;
      break;
    case 83:
      val[ 0 ] = 105.; val[ 1 ] = 115.88;val[ 2 ] = 128.57;
      break;
    case 84:
      val[ 0 ] = 106.; val[ 1 ] = 117.06;val[ 2 ] = 129.80;
      break;
    case 85:
      val[ 0 ] = 107.; val[ 1 ] = 118.24;val[ 2 ] = 131.04;
      break;
    case 86:
      val[ 0 ] = 108.; val[ 1 ] = 119.41;val[ 2 ] = 132.28;
      break;
    case 87:
      val[ 0 ] = 109.; val[ 1 ] = 120.59;val[ 2 ] = 133.51;
      break;
    case 88:
      val[ 0 ] = 110.; val[ 1 ] = 121.77;val[ 2 ] = 134.74;
      break;
    case 89:
      val[ 0 ] = 112.; val[ 1 ] = 122.94;val[ 2 ] = 135.96;
      break;
    case 90:
      val[ 0 ] = 113.; val[ 1 ] = 124.12;val[ 2 ] = 137.19;
      break;
    case 91:
      val[ 0 ] = 114.; val[ 1 ] = 125.29;val[ 2 ] = 138.45;
      break;
    case 92:
      val[ 0 ] = 115.; val[ 1 ] = 126.46;val[ 2 ] = 139.66;
      break;
    case 93:
      val[ 0 ] = 116.; val[ 1 ] = 127.63;val[ 2 ] = 140.90;
      break;
    case 94:
      val[ 0 ] = 117.; val[ 1 ] = 128.80;val[ 2 ] = 142.12;
      break;
    case 95:
      val[ 0 ] = 118.; val[ 1 ] = 129.97;val[ 2 ] = 143.32;
      break;
    case 96:
      val[ 0 ] = 119.; val[ 1 ] = 131.14;val[ 2 ] = 144.55;
      break;
    case 97:
      val[ 0 ] = 120.; val[ 1 ] = 132.31;val[ 2 ] = 145.78;
      break;
    case 98:
      val[ 0 ] = 122.; val[ 1 ] = 133.47;val[ 2 ] = 146.99;
      break;
    case 99:
      val[ 0 ] = 123.; val[ 1 ] = 134.64;val[ 2 ] = 148.21;
      break;
    case 100:
      val[ 0 ] = 124.; val[ 1 ] = 135.81;val[ 2 ] = 149.48;
      break;
    default:
      cerr << "Out of limit... approximating using 100 d.o.f. \n";
      val[ 0 ] = 124.; val[ 1 ] = 135.81;val[ 2 ] = 149.48;
      break;	   
  }
  return val[ ia ];
}
