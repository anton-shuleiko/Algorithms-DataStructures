#include <iostream>
#include <vector>

class Graph { 
 public:
    Graph(size_t size) {
        matrix_ = std::vector<std::vector<size_t>>(size);
        is_visited_ = std::vector<bool>(size, false);
        for(auto& matr: matrix_) {
            matr.resize(size);
        }
    }   
    void DepthFirst(size_t vertex, size_t target) {
        if (IsVisited(target)) {
            return;
        }
        GetVisited()[target] = true;
        for (int i = 0; i < matrix_.size(); ++i) {
            if (GetEdges(target)[i] == 1 && !IsVisited(i)) {
            DepthFirst(vertex, i);
            GetEdges(vertex)[i] = 1;        
            }
        }
    }

    bool IsVisited(size_t vertex) {
        return is_visited_[vertex];
    }
    std::vector<size_t>& GetEdges(size_t vertex) {
        return matrix_[vertex];
    }
    std::vector<bool>& GetVisited(){
        return is_visited_;
    }
    std::vector<std::vector<size_t>>& GetMatrix(){
        return matrix_;
    }
 private:
    std::vector<std::vector<size_t>> matrix_;
    std::vector<bool> is_visited_;

};


Graph InPut( ){
    size_t size = 0;
    std::cin >> size;
    Graph graph(size);
    for(auto& arr: graph.GetMatrix()) {
        for(auto& some_elem: arr ) {
            size_t len = 0;
            std::cin >> len;
            some_elem = len;
        }
    }
    return graph;
}
void Work(Graph& graph){
    size_t i = graph.GetMatrix().size();
    while((i--) > 0) {
        graph.GetVisited().assign(graph.GetMatrix().size(), false);
        graph.DepthFirst(i, i);
    }
}
void Output(Graph& graph){
        for(auto& arr: graph.GetMatrix()) {
            for(auto& some_elem: arr ) {
                std::cout << some_elem << " ";
            }
            std::cout << std::endl;
        }
}

int main() {
    Graph graph = InPut();
    Work(graph);
    Output(graph);
}