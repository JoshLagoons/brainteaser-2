
#include<iostream>
#include<algorithm>
#include<vector>
#include<memory>

struct Point
{
  int x;
  int x2;
  int y;
  int y2;
  Point(int x, int y, int x2, int y2)
  {
    this->x = x;
    this->x2 = x2;
    this->y = y;
    this->y2 = y2;
  }
};

class Graph
{
private:
  std::vector<Point*> * m_points;
public:
  Graph(){
    this->m_points = new std::vector<Point*>();
  }

  ~Graph()
  {
    delete(this->m_points);
  }

  void emplace(Point * p){
    m_points->push_back(p);
  }

  std::vector<Point *> * sort()
  {
    std::sort(this->m_points->begin(), this->m_points->end(), [](Point * lhs, Point * rhs){
        return (lhs->x > rhs->x);
        return (lhs->x2 > rhs -> x2);
      });
    return this->m_points;
  }
};


struct GraphEngine
{
private:
  std::shared_ptr<Graph> m_g;

public:
  GraphEngine(std::shared_ptr<Graph> g)
  {
    this->m_g = g;
  }

  float calculate_slope(){
    auto sorted = this->m_g->sort();
    Point * first = (*sorted->begin());
    Point * last = (*sorted->end());
    return (last->y2 - first->y) / (last->x2 - first->x);
  }
};

struct PointFactory
{
  static Point * createOrigin()
  {
    return new Point(0, 0, 0, 0);
  }
};




int main()
{
  std::shared_ptr<Graph> g = std::make_shared<Graph>();
  std::shared_ptr<GraphEngine> ge = std::make_shared<GraphEngine>(g);
  auto first = PointFactory::createOrigin();

  g->emplace(new Point(10, 10, 20, 20));
  g->emplace(new Point(20, 20, 30, 30));
  g->emplace(new Point(30, 30, 40, 40));

  auto slope = ge->calculate_slope();

  std::cout << slope << std::endl;
}

