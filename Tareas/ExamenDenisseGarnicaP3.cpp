/*
PROBLEMA 3: Denisse Garnica
Solucion:
Empezamos notando que la cuerda a usar esta definida por el Convex Hull de la
posicion de los puntos. Por lo que una vez tengamos los puntos que conforman al
Convex hull solo nos sera necesario calcular la suma de las distancias de los
puntos en orden que lo conforman.

Para calcular el convex hull usare el algoritmo de Graham, el cual sabemos tiene
una complejidad de O(n log n), despues el calculo de las distancias de las lineas
es constante. Pero al hacer n-1 veces entonces tenemos que la complejidad total
es O(n log n) + O(n-1) = O(n log n).
*/

#include<bits/stdc++.h>
#define ll long long
using namespace std;
#define EPS 0.0001


struct point {
  double x, y;
  // Only used if more precision is needed
  point() { x = y = 0.0; }
  // Default constructor
  point(double _x, double _y) : x(_x), y(_y) {}
  // Copy constructor
  point(const point &p) : x(p.x), y(p.y) {}
};


double dist(const point &p1, const point &p2) {
  return hypot(p1.x - p2.x, p1.y - p2.y);
}

struct vec{
  double x, y;
  vec(const double &_x, const double &_y) : x(_x), y(_y) {}
};

// Form a vector from 2 points
vec toVec(const point &a, const point &b) {
  // Convert 2 points to vector a->b
  return vec(b.x - a.x, b.y - a.y);
}

vec scale(const vec &v, double s) {
  return vec(v.x * s, v.y * s);
}

// Apply a translation
point translate(const point &p, const vec &v) {
// translate p according to v
  return point(p.x + v.x , p.y + v.y);
}

// Dot product between two vectors
double dot(const vec &a, const vec &b) { return (a.x * b.x + a.y * b.y); }
// Squared norm of a vector
double norm_sq(const vec &v) { return v.x * v.x + v.y * v.y; }

// Returns the distance from p to the line defined by
// two points a and b (a and b must be different)
// the closest point is stored in the 4th parameter (passed by ref)
double distToLine(const point &p, const point &a, const point &b, point &c) {
    // formula: c = a + u * ab
    vec ap = toVec(a, p), ab = toVec(a, b);
    double u = dot(ap, ab) / norm_sq(ab);
    c = translate(a, scale(ab, u)); // translate a to c
    return dist(p, c); // Euclidean distance between p and c
}


bool collinear(const point &pivot, const point &a, const point &b){
  point c;
  double aux = distToLine(b, a, pivot, c);
  if(aux < EPS)
    return 1;
  return 0;
}

point pivot(0, 0);

bool angleCmp(const point &a, const point &b) {
    // angle-sorting function
    if (collinear(pivot, a, b))
        // special case
        return dist(pivot, a) < dist(pivot, b); // check which one is closer

    double d1x = a.x - pivot.x, d1y = a.y - pivot.y;
    double d2x = b.x - pivot.x, d2y = b.y - pivot.y;
    return (atan2(d1y, d1x) - atan2(d2y, d2x)) < 0; // compare two angles
}

bool point_equal(const point &a, const point &b){
  if(abs(a.x - b.x) > EPS)
      return 0;
  if(abs(a.y - b.y) > EPS)
      return 0;
  return 1;
}

// Cross-product
double cross(const vec &a, const vec &b) {
  return a.x * b.y - a.y * b.x;
}

// Returns true if point r is on the left side of line pq
bool ccw(const point &p, const point &q, const point &r) {
  return cross(toVec(p, q), toVec(p, r)) > 0;
}

vector<point> CH_Graham(vector<point> &P) {
    // the content of P may be reshuffled
    int i, j, n = (int)P.size();
    if (n <= 3) { // special case, the CH is P itself
        if (!(point_equal(P[0], P[n-1])))
            P.push_back(P[0]); // safeguard from corner case
        return P;
    }
    // first, find P0 = point with lowest Y and if tie: rightmost X
    int P0 = 0;
    for (i = 1; i < n; i++)
        if (P[i].y < P[P0].y || (abs(P[i].y - P[P0].y) < EPS && P[i].x > P[P0].x))
            P0 = i;
    point temp = P[0];
    P[0] = P[P0];
    P[P0] = temp;
    // swap P[P0] with P[0]
    // second, sort points by angle w.r.t. pivot P0
    pivot = P[0]; // use this global variable as reference
    sort(++P.begin(), P.end(), angleCmp); // we do not sort P[0]
    // third, the ccw tests
    vector<point> S;
    S.push_back(P[n-1]); S.push_back(P[0]); S.push_back(P[1]);
    // initial S
    i = 2;
    // then, we check the rest
    while (i < n) {
        // note: N must be >= 3 for this method to work
        j = (int)S.size()-1;
        if (ccw(S[j-1], S[j], P[i]))
            S.push_back(P[i++]); // left turn, accept
        else
            S.pop_back(); // or pop the top of S until we have a left turn
    }
    return S;
}



int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  int N;
  std::cin >> N; //se ingresan numero de puntos
  vector<point> P;
  point aux;
  //ingresamos los N puntos
  for (int i = 0; i < N; i++) {
    std::cin >> aux.x >> aux.y;
    P.push_back(aux);
  }

  vector<point> CH =  CH_Graham(P); //recordemos que repite el primer y ultimo punto
std::cout  << '\n';
  for (int i = 0; i < CH.size()-1; i++) {
    std::cout << CH[i].x << " " << CH[i].y << '\n';
  }

  return 0;
  }
