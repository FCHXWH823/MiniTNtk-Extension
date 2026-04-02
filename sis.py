from pyeda.inter import expr
from pyeda.inter import espresso_exprs
import sys
def parse_bool_funcs_and_negate(txt):
    """
    Reads a file of lines in the format:
        FuncName(Count): BooleanExpression
    (e.g., "NSP 19(6): f*a + b + f*a*c + f*d + a*f*d*b*c")
    and returns a dict:
        {
          "NSP 19": {
             "transistors": 6,
             "negated_expr": "<sum-of-products in '!' '*' '+' form>",
             "num_unique_literals": <int>
          },
          ...
        }
    """

    def convert_to_pyeda_format(expr_str):
        """
        Convert from your '!' '*' '+' style to PyEDA-friendly format:
          - Replace '!' with '~'
          - Replace '*' with '&'
          - Replace '+' with '|'
        Also remove spaces.
        """
        expr_str = expr_str.replace(' ', '')
        expr_str = expr_str.replace('!', '~')
        expr_str = expr_str.replace('*', '&')
        expr_str = expr_str.replace('+', '|')
        return expr_str

    def convert_from_pyeda_format(expr_str):
        """
        Convert from PyEDA's '~' '&' '|' back to your '!' '*' '+' style.
        """
        expr_str = expr_str.replace('~', '!')
        expr_str = expr_str.replace('&', '*')
        expr_str = expr_str.replace('|', '+')
        return expr_str

    def get_dnf_terms(dnf_expr):
        """
        Given a PyEDA expression in DNF form, return a list of products,
        where each product is a list of literal strings, e.g.:
            (a & b) | (~c & d) --> [ ["a","b"], ["~c","d"] ]
        """
        if dnf_expr.is_zero():
            return []
        if dnf_expr.is_one():
            return [[]]
        # If it's an OR, each subexpression is a product
        if dnf_expr.ASTOP == 'or':
            terms = []
            for subexpr in dnf_expr.xs:
                terms.extend(get_dnf_terms(subexpr))
            return terms

        # If it's an AND, collect sub-literals in a single product
        if dnf_expr.ASTOP == 'and':
            product = []
            for subexpr in dnf_expr.xs:
                subterms = get_dnf_terms(subexpr)  # likely one product
                if subterms:
                    product.extend(subterms[0])
            return [product]

        # Otherwise, it's a single literal
        return [[str(dnf_expr)]]

    with open(txt) as file:
        bool_expr_str = file.read()

    # 1. Convert expression to PyEDA format
    pyeda_expr_str = convert_to_pyeda_format(bool_expr_str)

    # 2. Parse it with PyEDA
    expr_obj = expr(pyeda_expr_str)

    # 3. Negate and simplify
    neg_expr = ~expr_obj

    # 4. Convert to DNF (sum-of-products)
    dnf_expr = neg_expr.to_dnf()

    # 5. Break into product terms
    min_expr = espresso_exprs(dnf_expr)[0]
    terms = get_dnf_terms(min_expr)

    product_strings = []
    for product in terms:
        product_str = '&'.join(product)
        product_strings.append(product_str)
    # Join products with '|'
    final_pyeda_str = '|'.join(product_strings)

    # Now replace "~" with "!", "&" with "*", "|" with "+"
    final_expr_str = convert_from_pyeda_format(final_pyeda_str)
    with open("NegFunc_out.eqn","w") as eqn_file:
        eqn_file.write(f"Func = {final_expr_str};")


# ---------------------- Example Usage ----------------------
if __name__ == "__main__":
    data = parse_bool_funcs_and_negate(sys.argv[1])