#ifndef Lettura_h
#define Lettura_h

#include <ostream>


struct Lettura
{
	public:
	
	constexpr Lettura()
        : yaw_v(0), yaw_a(0),
          pitch_v(0), pitch_a(0),
          roll_v(0), roll_a(0)
    {}
    // Costruttore completo
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

    // Getters
    constexpr double get_yaw_v() const { return yaw_v; }
    constexpr double get_yaw_a() const { return yaw_a; }
    constexpr double get_pitch_v() const { return pitch_v; }
    constexpr double get_pitch_a() const { return pitch_a; }
    constexpr double get_roll_v() const { return roll_v; }
    constexpr double get_roll_a() const { return roll_a; }
	
	private:
		double yaw_v ;       	//vel intorno all'asse y
		double yaw_a;		//accell. intorno all'asse y
		double pitch_v;		//vel  intorno all'asse p
		double pitch_a; 	//accell. intorno all'asse p
		double roll_v;		//vel intorno all'asse r
		double roll_a;		//accell. intorno all'asse r
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