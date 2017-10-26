filename=Assignment1

pdf: ps
	ps2pdf ${filename}.ps

pdf-print: ps
	ps2pdf ${filename}.ps

ps:	dvi
	dvips ${filename}.dvi

dvi:
	latex ${filename}

clean:
	rm -f ${filename}.{ps,log,aux,out,dvi,bbl,blg}
