#pragma once

#include <memory>
#include <vector>

#include "moses/Syntax/S2T/Parsers/Parser.h"
#include "moses/Syntax/S2T/RuleTrieScope3.h"
#include "moses/WordsRange.h"

#include "PatternApplicationTrie.h"
#include "SymbolRangeCalculator.h"
#include "TailLattice.h"
#include "TailLatticeBuilder.h"

namespace Moses
{
namespace Syntax
{
namespace S2T
{

template<typename Callback>
class Scope3Parser : public Parser<Callback>
{
public:
  typedef Parser<Callback> Base;
  typedef RuleTrieScope3 RuleTrie;

  Scope3Parser(PChart &, const RuleTrie &, std::size_t);

  ~Scope3Parser();

  void EnumerateHyperedges(const WordsRange &, Callback &);

private:
  void Init();
  void InitRuleApplicationVector();
  void FillSentenceMap(SentenceMap &);
  void RecordPatternApplicationSpans(const PatternApplicationTrie &);

  PatternApplicationTrie *m_patRoot;
  std::vector<std::vector<bool> > m_quickCheckTable;
  const RuleTrie &m_ruleTable;
  const std::size_t m_maxChartSpan;
  TailLattice m_lattice;
  TailLatticeBuilder m_latticeBuilder;
  SymbolRangeCalculator m_symbolRangeCalculator;
  std::vector<SymbolRange> m_symbolRanges;
  PatternApplicationKey m_patKey;

  /* m_patSpans[i][j] records the set of all PAT nodes for span [i,i+j]
     i.e. j is the width of the span */
  std::vector<std::vector<
    std::vector<const PatternApplicationTrie *> > > m_patSpans;
};

}  // namespace S2T
}  // namespace Syntax
}  // namespace Moses

// Implementation
#include "Parser-inl.h"
