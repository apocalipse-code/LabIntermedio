#ifndef Lettura_h
#define Lettura_h

#include <ostream>


struct Lettura
{
	const double yaw_v ;       	//vel intorno all'asse y
	const double yaw_a;		//accell. intorno all'asse y
	const double pitch_v;		//vel  intorno all'asse p
	const double pitch_a; 	//accell. intorno all'asse p
	const double roll_v;		//vel intorno all'asse r
	const double roll_a;		//accell. intorno all'asse r		
	
	// costruttore di default
	Lettura():yaw_v(0.0), yaw_a(0.0), pitch_v(0.0), pitch_a(0.0), roll_v(0.0), roll_a(0.0){};

	// costruttore di parametri
	Lettura(double yVel, double yAcc, double pVel, double pAcc,double rVel, double rAcc)
	:yaw_v(yVel), yaw_a(yAcc), pitch_v(pVel), pitch_a(pAcc), roll_v(rVel), roll_a(rAcc){};
	
};

		
//Operatore <<
inline std::ostream& operator<<(std::ostream& out, const Lettura& l){
	out << "(";
	out << "yaw_v: " << l.yaw_v << ", ";
	out << "yaw_a: " << l.yaw_a << ", ";
	out << "pitch_v: " << l.pitch_v << ", ";
	out << "pitch_a: " << l.pitch_a << ", ";
	out << "roll_v: " << l.roll_v << ", ";
	out << "roll_a: " << l.roll_a << ", ";
	out << ")";
	
	return out;
}


#endif