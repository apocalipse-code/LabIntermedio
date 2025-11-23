#ifndef Lettura_h
#define Lettura_h

#include <ostream>

//Significato di questa struttura dato:
/*
	Motivo della scelta: abbiamo concordato sul fatto che i valori raccolti da un sensore
	debbano essere rappresentati come un'unità fissa, compatta, poco malleabile e il meno
	possibile modificabile. La struct è un ottimo esempio di raccolta di dati compatta e semplice,
	che si adatta a questo scopo. Tuttavia, abbiamo dovuto prendere dei provvedimenti per fare in
	modo che i dati non fossero facilmente modificabili e abbiamo deciso di renderli privati, dato
	che secondo noi non ha senso modificare dei dati raccolti da un sensore.
    Siamo consapevoli che una struct nasce per essere pubblica e senza funzioni, ma abbiamo deciso 
    comunque questo design ibrido.  
*/

struct Lettura
{
	public:
	
	//costruttore di default
	constexpr Lettura()
        : yaw_v(0), yaw_a(0),
          pitch_v(0), pitch_a(0),
          roll_v(0), roll_a(0)
    {}
	
    //costruttore con parametri
    constexpr Lettura(
        double yaw_v,
        double yaw_a,
        double pitch_v,
        double pitch_a,
        double roll_v,
        double roll_a)
         :yaw_v(yaw_v),
          yaw_a(yaw_a),
          pitch_v(pitch_v),
          pitch_a(pitch_a),
          roll_v(roll_v),
          roll_a(roll_a)
    {}

    //getter
    constexpr double get_yaw_v() const { return yaw_v; }
    constexpr double get_yaw_a() const { return yaw_a; }
    constexpr double get_pitch_v() const { return pitch_v; }
    constexpr double get_pitch_a() const { return pitch_a; }
    constexpr double get_roll_v() const { return roll_v; }
    constexpr double get_roll_a() const { return roll_a; }
	
	private:
		double yaw_v ;       	//vel intorno all'asse yaw
		double yaw_a;		//accell. intorno all'asse yaw
		double pitch_v;		//vel  intorno all'asse pitch
		double pitch_a; 	//accell. intorno all'asse pitch
		double roll_v;		//vel intorno all'asse roll
		double roll_a;		//accell. intorno all'asse roll
};

		
//Operatore <<
inline std::ostream& operator<<(std::ostream& out, const Lettura& l){
	out << "(";
	out << "yaw_v: " << l.get_yaw_v() << ", ";
	out << "yaw_a: " << l.get_yaw_a() << ", ";
	out << "pitch_v: " << l.get_pitch_v() << ", ";
	out << "pitch_a: " << l.get_pitch_a() << ", ";
	out << "roll_v: " << l.get_roll_v() << ", ";
	out << "roll_a: " << l.get_roll_a() << ", ";
	out << ")";
	
	return out;
}


#endif