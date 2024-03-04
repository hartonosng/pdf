import streamlit as st
import fitz
from PIL import Image
import io

def pdf_to_image(pdf_file):
    images = []
    pdf_document = fitz.open(stream=pdf_file, filetype="pdf")
    first_page = pdf_document[0]
    image = first_page.get_pixmap()
    img_bytes = io.BytesIO(image.get_png_data())
    img = Image.open(img_bytes)
    images.append(img)
    return images

def main():
    st.title("PDF and Image Viewer")

    uploaded_file = st.file_uploader("Upload a PDF or Image", type=["pdf", "png", "jpg", "jpeg"])

    if uploaded_file is not None:
        file_type = uploaded_file.type.split("/")[1]
        if file_type == "pdf":
            images = pdf_to_image(uploaded_file)
            st.image(images, caption="PDF converted to Image (First Page)", use_column_width=True)
        else:
            st.image(uploaded_file, caption="Uploaded Image", use_column_width=True)

if __name__ == "__main__":
    main()
