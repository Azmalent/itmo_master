using UnityEngine;
using UnityEngine.EventSystems;
using UnityEngine.UI;

public class ElementInstance : MonoBehaviour, IBeginDragHandler, IDragHandler, IEndDragHandler, IDropHandler
{
    public Canvas Canvas;
    public Element Type;

    private RectTransform rectTransform;
    private CanvasGroup canvasGroup;
    private Image image;

    private void Awake()
    {
        rectTransform = GetComponent<RectTransform>();
        canvasGroup = GetComponent<CanvasGroup>();
        image = GetComponent<Image>();
    }

    public void OnBeginDrag(PointerEventData eventData)
    {
        canvasGroup.alpha = 0.5f;
        canvasGroup.blocksRaycasts = false;
    }

    public void OnDrag(PointerEventData eventData)
    {
        rectTransform.anchoredPosition += eventData.delta / Canvas.scaleFactor;
    }

    public void OnEndDrag(PointerEventData eventData)
    {
        canvasGroup.alpha = 1f;
        canvasGroup.blocksRaycasts = true;
    }

    public void OnDrop(PointerEventData eventData)
    {
        if (eventData.pointerDrag != null)
        {
            var other = eventData.pointerDrag.GetComponent<ElementInstance>();
            if (other != null)
            {
                var output = ReactionHandler.GetReactionResult(Type, other.Type);
                if (output != null)
                {
                    Destroy(other.gameObject);
                    this.Type = (Element) output;
                    this.image.sprite = Resources.Load<Sprite>("Textures/" + Type.ToString().ToLower());
                }
            }
        }
    }
}
