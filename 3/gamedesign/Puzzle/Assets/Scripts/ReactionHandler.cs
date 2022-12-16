using System.Collections.Generic;
using UnityEngine;

public class ReactionHandler
{
    private static Dictionary<Element, Dictionary<Element, Element>> reactions = new Dictionary<Element, Dictionary<Element, Element>>();

    private static void AddReaction(Element first, Element second, Element output)
    {
        if (!reactions.ContainsKey(first))
        {
            reactions[first] = new Dictionary<Element, Element>();
        }

        if (!reactions.ContainsKey(second))
        {
            reactions[second] = new Dictionary<Element, Element>();
        }

        reactions[first][second] = output;

        if (first != second)
        {
            reactions[second][first] = output;
        }
    }

    static ReactionHandler()
    {
        AddReaction(Element.Air, Element.Fire, Element.Energy);
        AddReaction(Element.Air, Element.Earth, Element.Dust);
        AddReaction(Element.Air, Element.Water, Element.Ice);
        AddReaction(Element.Water, Element.Earth, Element.Seed);
        AddReaction(Element.Water, Element.Fire, Element.Steam);
        AddReaction(Element.Fire, Element.Earth, Element.Metal);
        AddReaction(Element.Earth, Element.Earth, Element.Rock);
        AddReaction(Element.Dust, Element.Water, Element.Clay);
        AddReaction(Element.Mould, Element.Metal, Element.Key);
        AddReaction(Element.Clay, Element.Fire, Element.Mould);
        AddReaction(Element.Seed, Element.Earth, Element.Tree);
    }

    public static Element? GetReactionResult(Element first, Element second)
    {
        if (reactions.ContainsKey(first))
        {
            if (reactions[first].ContainsKey(second))
            {
                return reactions[first][second];
            }
        }

        return null;
    }
}