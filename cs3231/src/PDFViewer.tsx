import React from 'react';
import { PdfLoader, PdfHighlighter, Tip, Highlight, Popup } from 'react-pdf-highlighter';

interface MyPdfViewerProps {
    filePath: string;
}

const MyPdfViewer: React.FC<MyPdfViewerProps> = ({ filePath }) => (
    <PdfLoader
        url={filePath}
        beforeLoad={<div>Loading PDF...</div>}  // Render this before the PDF loads
    >
        {(pdfDocument) => (
            <PdfHighlighter
                pdfDocument={pdfDocument}
                highlights={[]}
                highlightTransform={(highlight, index, setTip, hideTip, viewportToScaled, screenshot, isScrolledTo) => (
                    <div
                        key={index}
                        style={{
                            backgroundColor: isScrolledTo ? 'yellow' : 'transparent',
                            padding: '5px',
                            borderRadius: '3px',
                        }}
                    >
                        <strong>{highlight.comment.text}</strong>
                    </div>
                )}
                onScrollChange={() => {}}
                scrollRef={(scrollTo) => {}}
                onSelectionFinished={(position, content, hideTipAndSelection) => (
                    <Tip
                        onOpen={hideTipAndSelection}
                        onConfirm={(comment) => {
                            console.log(comment);
                        }}
                    />
                )}
                enableAreaSelection={(event) => true}
            />
        )}
    </PdfLoader>
);

export default MyPdfViewer;
