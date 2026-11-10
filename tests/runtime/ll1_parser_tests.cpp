// test file is almost completely ai-generated


// ============================================================
// LL(1) parser regression tests
// ============================================================
//
// Requires: ll1_parser_fixed.h
//
// All grammar rules are created using make_rule(), following
// the same pattern as the application:
//
//   nonterminals.init();
//   gram_rule_t::gram_rules rules;
//   rules.init();
//   rules.append(make_rule("$Start -> @ident",
//                          callback, &nonterminals));
//
// The parser header declares lex_string(), but its implementation
// was not included in the original upload. A small test lexer is
// therefore provided below.
//
// Compile:
//   g++ -std=c++11 -Wall -Wextra -O2 {\}
//       ll1_parser_tests.cpp -o ll1_tests
//
// Run:
//   ./ll1_tests
//
// Sanitizers:
//   g++ -std=c++11 -g -fsanitize=address,undefined {\}
//       -fno-omit-frame-pointer ll1_parser_tests.cpp -o ll1_tests
//
// ============================================================

#include "lexer.cpp"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <string>
#include <vector>
#include <initializer_list>

// POSIX subprocess support for testing parser errors.
#if defined(__unix__) || defined(__APPLE__)
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#define LL1_HAS_POSIX_SUBPROCESS 1
#else
#define LL1_HAS_POSIX_SUBPROCESS 0
#endif

// ============================================================
// Test infrastructure
// ============================================================

namespace {

using RuleList = gram_rule_t::gram_rules;
using Join = anyptr (*)(clist_anyptr);

typedef decltype(token{}.kind) TokenKind;

int tests_run = 0;
int tests_failed = 0;

#define CHECK(condition)                                      \
    do {                                                      \
        ++tests_run;                                          \
        if (!(condition)) {                                   \
            ++tests_failed;                                   \
            std::fprintf(stderr,                              \
                "FAIL %s:%d: %s\n",                           \
                __FILE__, __LINE__, #condition);              \
            exit(EXIT_FAILURE);                               \
        } else {                                              \
            std::printf("success %s:%d: %s\n",                \
                __FILE__, __LINE__, #condition);              \
        }                                                     \
    } while (0)

// ------------------------------------------------------------
// Token helpers
// ------------------------------------------------------------

token ident(const char* text) {
    token t{};
    t.kind = token::Ident;
    t.dat.Ident_dat.str = text;
    return t;
}

token punctuation(TokenKind kind) {
    token t{};
    t.kind = kind;
    return t;
}

// ------------------------------------------------------------
// Semantic values
// ------------------------------------------------------------

void free_int(void* p) {
    std::free(p);
}

anyptr make_int(int value) {
    int* p = static_cast<int*>(std::malloc(sizeof(int)));

    if (p == nullptr)
        std::abort();

    *p = value;

    anyptr result;
    result.init(p, free_int);

    return result;
}

int int_arg(clist_anyptr args, int index) {
    anyptr p = args.ith(index);
    return *static_cast<int*>(p.get());
}

token* token_arg(clist_anyptr args, int index) {
    anyptr p = args.ith(index);
    return static_cast<token*>(p.get());
}

// ------------------------------------------------------------
// Semantic callbacks
// ------------------------------------------------------------

anyptr return_one(clist_anyptr) {
    return make_int(1);
}

anyptr return_zero(clist_anyptr) {
    return make_int(0);
}

anyptr return_two(clist_anyptr) {
    return make_int(2);
}

// Checks that AST children are evaluated in source order.
anyptr evaluate_wrapped_identifier(clist_anyptr args) {

    token* open = token_arg(args, 0);
    token* value = token_arg(args, 1);
    token* close = token_arg(args, 2);

    CHECK (open->kind == token::Ident &&
        std::strcmp(open->dat.Ident_dat.str, "open") == 0);
    CHECK (value->kind == token::Ident &&
        std::strcmp(value->dat.Ident_dat.str, "payload") == 0);
    CHECK (close->kind == token::Ident &&
        std::strcmp(close->dat.Ident_dat.str, "close") == 0);


    return make_int(42);
}

// Start -> OptionalA b
anyptr evaluate_optional_sequence(clist_anyptr args) {
    return make_int(int_arg(args, 0));
}

// ============================================================
// Grammar construction helpers
// ============================================================

RuleList make_rule_list() {
    RuleList rules;
    rules.init();
    return rules;
}

// This is the same rule-building pattern used by the application.
gram_rule_t* add_rule(
    RuleList& rules,
    string_list& nonterminals,
    const char* source,
    Join callback
) {
    gram_rule_t* rule =
        make_rule(source, callback, &nonterminals);

    if (rule == nullptr)
        std::abort();

    rules.append(rule);

    return rule;
}

// Release grammar allocations.
void cleanup_rules(
    RuleList& rules,
    string_list& nonterminals
) {
    while (rules.len() > 0) {

        gram_rule_t* rule = rules.pop();

        if (rule != nullptr) {
            rule->pattern.del();
            std::free(rule);
        }
    }

    while (nonterminals.len() > 0) {
        const char* name = nonterminals.pop();

        std::free(const_cast<char*>(name));
    }
}

// ============================================================
// Input construction
// ============================================================

toklist make_input(
    std::initializer_list<token> source_order
) {
    toklist result;
    result.init();

    std::vector<token> tokens(source_order);

    for (auto it = tokens.rbegin(); it != tokens.rend(); ++it) {
        result.push(*it);
    }

    return result;
}

// ============================================================
// Parsing helpers
// ============================================================

int parse_int(
    toklist& input,
    int goal,
    gram_rule_t::gram_symbol_t stop,
    RuleList rules,
    string_list nonterminals
) {
    anyptr result =
        gram_rule_t::parse_with_rules(
            &input,
            goal,
            stop,
            rules,
            nonterminals
        );

    int value = *static_cast<int*>(result.get());

    result.del();

    return value;
}

gram_rule_t::gram_symbol_t exact_stop(token t) {
    gram_rule_t::gram_symbol_t stop{};
    stop.set_exact(t);
    return stop;
}

// ============================================================
// TEST 1
// Exact terminals, category terminals and AST ordering
// ============================================================

void test_exact_and_category_terminals() {

    RuleList rules = make_rule_list();

    string_list names;
    names.init();

    add_rule(
        rules,
        names,
        "$Start -> open @ident close",
        evaluate_wrapped_identifier
    );

    CHECK(names.len() == 1);
    CHECK(std::strcmp(names.ith(0), "Start") == 0);

    toklist input = make_input({
        ident("open"),
        ident("payload"),
        ident("close")
    });

    for (int i = 0; i < rules.len(); i++)
    {
      rules.ith(i)->print(names);
    }
    

    int value = parse_int(
        input,
        0,
        exact_stop(punctuation(token::EndOfInput)),
        rules,
        names
    );

    CHECK(value == 42);
    CHECK(input.len() == 0);

    input.del();

    cleanup_rules(rules, names);
}

// ============================================================
// TEST 2
// Multiple alternatives selected by lookahead
// ============================================================

int parse_alternative(const char* word) {

    RuleList rules = make_rule_list();

    string_list names;
    names.init();

    add_rule(
        rules,
        names,
        "$Start -> alpha",
        return_one
    );

    add_rule(
        rules,
        names,
        "$Start -> beta",
        return_two
    );

    toklist input = make_input({
        ident(word)
    });

    int value = parse_int(
        input,
        0,
        exact_stop(punctuation(token::EndOfInput)),
        rules,
        names
    );

    input.del();

    cleanup_rules(rules, names);

    return value;
}

void test_alternative_selection() {

    CHECK(parse_alternative("alpha") == 1);
    CHECK(parse_alternative("beta") == 2);
}

// ============================================================
// TEST 3
// Epsilon production selected using FOLLOW
// ============================================================

void test_epsilon_follow_set() {

    RuleList rules = make_rule_list();

    string_list names;
    names.init();

    add_rule(
        rules,
        names,
        "$Start -> $OptionalA b",
        evaluate_optional_sequence
    );

    add_rule(
        rules,
        names,
        "$OptionalA -> a",
        return_one
    );

    add_rule(
        rules,
        names,
        "$OptionalA ->",
        return_zero
    );

    CHECK(names.len() == 2);
    CHECK(std::strcmp(names.ith(0), "Start") == 0);
    CHECK(std::strcmp(names.ith(1), "OptionalA") == 0);

    gram_rule_t::gram_symbol_t eoi =
        exact_stop(punctuation(token::EndOfInput));

    // OptionalA is absent.
    toklist absent = make_input({
        ident("b")
    });

    CHECK(parse_int(absent, 0, eoi, rules, names) == 0);
    CHECK(absent.len() == 0);

    absent.del();

    // OptionalA is present.
    toklist present = make_input({
        ident("a"),
        ident("b")
    });

    CHECK(parse_int(present, 0, eoi, rules, names) == 1);
    CHECK(present.len() == 0);

    present.del();

    cleanup_rules(rules, names);
}

// ============================================================
// TEST 4
// Start symbol can derive epsilon
// ============================================================

void test_start_epsilon() {

    RuleList rules = make_rule_list();

    string_list names;
    names.init();

    add_rule(
        rules,
        names,
        "$Start ->",
        return_zero
    );

    toklist input = make_input({});

    int value = parse_int(
        input,
        0,
        exact_stop(punctuation(token::EndOfInput)),
        rules,
        names
    );

    CHECK(value == 0);
    CHECK(input.len() == 0);

    input.del();

    cleanup_rules(rules, names);
}

// ============================================================
// TEST 5
// Stop token must remain in the input
// ============================================================

void test_stop_token_preserved() {

    RuleList rules = make_rule_list();

    string_list names;
    names.init();

    add_rule(
        rules,
        names,
        "$Start -> $item",
        return_one
    );

    token semicolon = punctuation(token::Semicol);

    gram_rule_t::gram_symbol_t stop =
        exact_stop(semicolon);

    toklist input = make_input({
        ident("item"),
        semicolon
    });

    int value = parse_int(
        input,
        0,
        stop,
        rules,
        names
    );

    CHECK(value == 1);

    CHECK(input.len() == 1);

    CHECK(input.ith(0).eq(semicolon));

    input.del();

    cleanup_rules(rules, names);
}

// ============================================================
// TEST 6
// Invalid input must be rejected
// ============================================================

#if LL1_HAS_POSIX_SUBPROCESS

void test_invalid_input_rejected() {

    RuleList rules = make_rule_list();

    string_list names;
    names.init();

    add_rule(
        rules,
        names,
        "$Start -> $expected",
        return_one
    );

    gram_rule_t::gram_symbol_t eoi =
        exact_stop(punctuation(token::EndOfInput));

    pid_t child = fork();

    CHECK(child >= 0);

    if (child == 0) {

        std::freopen("/dev/null", "w", stderr);

        toklist input = make_input({
            ident("unexpected")
        });

        (void)gram_rule_t::parse_with_rules(
            &input,
            0,
            eoi,
            rules,
            names
        );

        // Reaching here means invalid input was accepted.
        std::_Exit(0);
    }

    if (child > 0) {

        int status = 0;

        CHECK(waitpid(child, &status, 0) == child);

        CHECK(WIFEXITED(status));

        CHECK(WEXITSTATUS(status) != 0);
    }

    cleanup_rules(rules, names);
}

// ============================================================
// TEST 7
// Ambiguous grammar must be rejected
// ============================================================

void test_ambiguous_grammar_rejected() {

    RuleList rules = make_rule_list();

    string_list names;
    names.init();

    add_rule(
        rules,
        names,
        "$Start -> $name",
        return_one
    );

    add_rule(
        rules,
        names,
        "$Start -> @ident",
        return_zero
    );

    gram_rule_t::gram_symbol_t eoi =
        exact_stop(punctuation(token::EndOfInput));

    pid_t child = fork();

    CHECK(child >= 0);

    if (child == 0) {

        std::freopen("/dev/null", "w", stderr);

        toklist input = make_input({
            ident("name")
        });

        (void)gram_rule_t::parse_with_rules(
            &input,
            0,
            eoi,
            rules,
            names
        );

        // The conflicting productions should not be accepted.
        std::_Exit(0);
    }

    if (child > 0) {

        int status = 0;

        CHECK(waitpid(child, &status, 0) == child);

        CHECK(WIFEXITED(status));

        CHECK(WEXITSTATUS(status) != 0);
    }

    cleanup_rules(rules, names);
}

#endif

// ============================================================
// TEST 8
// Grammar builder creates multiple nonterminals correctly
// ============================================================

void test_nonterminal_registration() {

    RuleList rules = make_rule_list();

    string_list names;
    names.init();

    add_rule(
        rules,
        names,
        "$Start -> $Expression",
        return_one
    );

    add_rule(
        rules,
        names,
        "$Expression -> $value",
        return_two
    );

    CHECK(names.len() == 2);

    CHECK(std::strcmp(names.ith(0), "Start") == 0);

    CHECK(std::strcmp(names.ith(1), "Expression") == 0);

    cleanup_rules(rules, names);
}

// ============================================================
// TEST 9
// Category terminal matches identifiers other than exact text
// ============================================================

void test_category_terminal() {

    RuleList rules = make_rule_list();

    string_list names;
    names.init();

    add_rule(
        rules,
        names,
        "$Start -> @ident",
        return_one
    );

    toklist input = make_input({
        ident("another_identifier")
    });

    int value = parse_int(
        input,
        0,
        exact_stop(punctuation(token::EndOfInput)),
        rules,
        names
    );

    CHECK(value == 1);
    CHECK(input.len() == 0);

    input.del();

    cleanup_rules(rules, names);
}

} // namespace

// ============================================================
// Main
// ============================================================

int main() {

    std::printf("\n");
    std::printf("====================================\n");
    std::printf("       LL(1) PARSER TESTS\n");
    std::printf("====================================\n\n");

    test_exact_and_category_terminals();

    test_alternative_selection();

    test_epsilon_follow_set();

    test_start_epsilon();

    test_stop_token_preserved();

    test_nonterminal_registration();

    test_category_terminal();

#if LL1_HAS_POSIX_SUBPROCESS

    test_invalid_input_rejected();

    test_ambiguous_grammar_rejected();

#else

    std::printf(
        "NOTE: Error-path tests skipped "
        "(POSIX subprocess support unavailable).\n"
    );

#endif

    std::printf("\n");
    std::printf("------------------------------------\n");

    std::printf(
        "Checks:  %d\n",
        tests_run
    );

    std::printf(
        "Failed:  %d\n",
        tests_failed
    );

    std::printf("------------------------------------\n");

    if (tests_failed == 0) {
        std::printf("ALL TESTS PASSED\n");
    }
    else {
        std::printf("SOME TESTS FAILED\n");
    }

    return tests_failed == 0 ? 0 : 1;
}
