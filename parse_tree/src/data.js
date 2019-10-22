export default {
  name: "S",
  str: " ",
  NodeType: "N-T",
  children: [
    {
      name: "A",
      str: " ",
      NodeType: "N-T",
      children: [
        { 
          name: "e",
          str: "SAe",
          NodeType: "T"
        },
        { 
          name: "*",
          str: "SA*",
          NodeType: "T",
        },
        {
          name: "f",
          str: "SAf",
          NodeType: "T"
        }
      ]
    },
    {
      name: "B",
      str: " ",
      NodeType: "N-T",
      children: [
        {
          name: "(",
          str: "SB(",
          NodeType: "T",
        },
        {
          name: "v",
          str: "SBv",
          NodeType: "T",
        },
        { 
          name: "g", 
          str: "SBg",
          NodeType: "T"
        },
        {
          name: ")",
          str: "SB)",
          NodeType: "T"
        }
      ]
    }
  ]
}
