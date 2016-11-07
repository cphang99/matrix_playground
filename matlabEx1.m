function  D=mydist4( X )
      
     if isempty(X)
          error('Input matrix is empty \n');
            
     end
      
     % Get the number of points .
    [NumberOfPoints dim]=size(X); 
     
    if NumberOfPoints<2
        error('Number of points should be more than one \n'); 
          
    end
     
     
 
   [n,m]=size(X);
   tic
   D = sqrt(sum(X.^2,2)*ones(1,n)+ones(n,1)*sum(X.^2,2)'-2*(X*X'));
 
   toc
 
 
end
%- See more at: http://www.codemiles.com/matlab-examples/vectorized-matlab-function-calculate-euclidean-distance-t10913.html#sthash.duuKi92p.dpuf
