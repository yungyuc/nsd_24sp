// line.hpp
#ifndef LINE_HPP
#define LINE_HPP

#include <vector>
#include <cstddef> // standard
// 定義line class
class Line{
    public:
        // Constructer:empty line
        Line();
        // Constructer:創建size大小line
        explicit Line(size_t size);

        // Copy_Constructer: 傳入Line (class) *const:表示line不能在func內被修改
        Line(const Line &line);
        // Move_Constructer : C++11 右值
        Line(Line &&line) noexcept;

        // move operator: 提供賦值作用
        Line& operator = (const Line &line);
        // move operator: 准許給予臨時值並且noexcept編譯器tends to 使用
        Line& operator = (Line &&line) noexcept;
        
        ~Line(); // 離開時釋放資源(銷毀)

        // func: return size_t 型態; const指定
        size_t size() const; // 這個函數不會修改對象成員狀態 若會 , error
        // return x[index] reference , x 為 private 成員 , 調用x()時連帶會改變
        float const& x(size_t index) const; 
        float& x(size_t it);
        // Y
        float const& y(size_t index) const;
        float& y(size_t index);

    private:
        std::vector<float> x_coords;
        std::vector<float> y_coords;
}; // class tail + ;

#endif // LINE_HPP
