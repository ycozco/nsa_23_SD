#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

bool esEtiquetaHTML(const std::string& cadena, const std::vector<std::string>& etiquetasValidas) {
    if (cadena.size() < 3 || cadena[0] != '<' || cadena[cadena.size() - 1] != '>') {
        return false; // No comienza y termina con < >
    }

    std::string contenido = cadena.substr(1, cadena.size() - 2); // Obtener el contenido sin < >
    
    for (const auto& etiqueta : etiquetasValidas) {
        if (contenido == etiqueta) {
            return true; // El contenido está en el arreglo de etiquetas válidas
        }
    }

    return false; // El contenido no es una etiqueta válida
}

int main() {
    std::vector<std::string> etiquetasValidas = { "a", "abbr", "address", "area", "article", "aside", "audio", "b", "base", "bdi", "bdo", "blockquote", "body", "br", "button", "canvas", "caption", "cite", "code", "col", "colgroup", "data", "datalist", "dd", "del", "details", "dfn", "dialog", "div", "dl", "dt", "em", "embed", "fieldset", "figcaption", "figure", "footer", "form", "h1", "h2", "h3", "h4", "h5", "h6", "head", "header", "hr", "html", "i", "iframe", "img", "input", "ins", "kbd", "label", "legend", "li", "link", "main", "map", "mark", "meta", "meter", "nav", "noscript", "object", "ol", "optgroup", "option", "output", "p", "param", "picture", "pre", "progress", "q", "rb", "rp", "rt", "rtc", "ruby", "s", "samp", "script", "section", "select", "slot", "small", "source", "span", "strong", "style", "sub", "summary", "sup", "svg", "table", "tbody", "td", "template", "textarea", "tfoot", "th", "thead", "time", "title", "tr", "track", "u", "ul", "var", "video", "wbr" };

    std::string ejemplos[] = {
        "<html>",
        "<div>",
        "<a>",
        "<invalid>",
        "<p>",
        "<span>"
    };

    for (const auto& ejemplo : ejemplos) {
        std::cout << "Cadena: " << ejemplo << " - Es etiqueta HTML: " << (esEtiquetaHTML(ejemplo, etiquetasValidas) ? "Si" : "No") << std::endl;
    }
    return 0;
}
